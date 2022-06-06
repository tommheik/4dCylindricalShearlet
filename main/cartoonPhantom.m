function [Pcoarse, Pfull] = cartoonPhantom(N, fine, coarse, skip)
% CARTOONFUNCTION creates 4D cylindrical cartoon-like phantom by abusing
% the excellent phantom3d code by Matthias Christian Schabel
% (matthias @ stanfordalumni . org)
%
% INPUT
% N:        The spatial resolution. For different z-length, one must use 
%           interpolation because phantom3d only supports uniform resolution.
% fine:     The number of small changes meant for simulating single
%           sinogram, this fine resolution movement is only shown in Pfull
% coarse:   The number of large scale time steps
% skip:     The amount of fine time steps that are skipped between each
%           coarse time step
%
% OUTPUT
% Pcoarse:  Phantom P containing only the coarse time steps. Pcoarse has
%           size [N x N x N x coarse].
% Pfull:    Phantom P containing all time steps (for simulating a sinogram
%           for example). Pfull has size [N x N x N x fine*coarse].
%
% T. Heikkilä   2022

Ttotal = (fine+skip)*coarse;
Pfull = zeros([N, N, N, fine*coarse], 'single');

Tind = 1:Ttotal;
for tt = 1:coarse
    Tind(tt*fine+1:tt*fine+skip) = []; % Remove skipped time steps
end
Tind = reshape(Tind,fine,coarse);

function out = skipSkips(in, ind)
    % Shorthand function to skip indicies and force output to point in the
    % 4th direction
    out = reshape(in(ind), 1, 1, 1, []);
end

%         A      a     b     c     x0      y0      z0     phi   theta    psi
%        -------------------------------------------------------------------
e =    [ .4   .700  .920  .810   -.01       0       0      10      10      0   % Outer shell
         .4   .680  .890  .790   -.01    .005       0      10      10      0   % Inner shell
        -.5   .640  .860  .765      0   -.010    .005      10      10      0   % Interior
         .2   .200  .350  .335    .25   -.350    -.05     -25       0      5   % Twin 1 (bottom left)
        .45   .200  .350  .335   -.25    .350     .05     -25       0      5   % Twin 2 (top right)
         .7   .070  .060  .750    .01   -.005     .02       0      10     10   % Spine
         .3   .060  .055  .310   -.35   -.250    -.02       0       0      0   % Medium
         .3   .045  .030  .320   -.20   -.220    -.01       0       0      0   % Small
         .3   .030  .027  .230   -.25   -.370       0       0       0      0]; % Tiny
    
tempChanges = [     skipSkips(linspace(1, 1.5, Ttotal),   Tind(:))             % Linear increase
                    skipSkips(linspace(1, 1.2, Ttotal),   Tind(:))             % Minor linear increase
                    skipSkips(linspace(1, 1.5, Ttotal),   Tind(:))             % Linear decrease (A is negative)
                    skipSkips(linspace(1, 2, Ttotal),     Tind(:))             % Linear increase
                    skipSkips(linspace(1, .5, Ttotal),    Tind(:))             % Linear Decrease
            .7+0.3*cos(skipSkips(linspace(0,2*pi,Ttotal),Tind(:)))             % Periodic
            .55+0.45*cos(skipSkips(linspace(pi,3*pi,Ttotal),Tind(:)))          % Periodic (phase = pi)
            .55+0.45*cos(skipSkips(linspace(.33*pi,2.33*pi,Ttotal),Tind(:)))   % Periodic (phase = .33*pi)
            .55+0.45*cos(skipSkips(linspace(-.33*pi,1.66*pi,Ttotal),Tind(:)))];% Periodic (phase = -.33*pi)
    
for j = 1:size(e,1)
    % phantom3d.m is part of tomobox by Jakob Heide Jørgensen:
    % https://se.mathworks.com/matlabcentral/fileexchange/28496-tomobox
    blop = phantom3d(N, e(j,:));
    Pfull = Pfull + blop .* tempChanges(j,:,:,:);
    
    % Smooth shell and interior with Gaussian
    if j == 3
        t = 5;
        gauss = 0.5*exp(-t*linspace(-1, 1, N).^2) + 0.5;
        Pfull = Pfull .* gauss .* gauss(:) .* reshape(gauss, [1, 1, N]);
    end
end

% Pick central fine time step for the ground truth
Pcoarse = Pfull(:,:,:,floor(fine/2)+1:fine:end);
end