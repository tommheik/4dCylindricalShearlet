% Generates X, Y, Z (cartesian coordiantes of polar coordinates)
% INPUT: cubeSide:: size of 3d cubeSide
% OUTPUT: P:: X, Y, Z coordinates of the cone / hyperpyramid 1, 2 ,3
function P = GeneratePyramidSection(cubeSide)
P = cell(1,3);
% Cone 1
[P{1}.X,P{1}.Y,P{1}.Z]= GenerateXYZ(cubeSide);

% Cone 2
P{2}.Y=P{1}.X;
P{2}.X=P{1}.Y;
P{2}.Z=P{1}.Z;

% Cone 3
P{3}.Z=P{1}.X;
P{3}.Y=P{1}.Y;
P{3}.X=P{1}.Z;

