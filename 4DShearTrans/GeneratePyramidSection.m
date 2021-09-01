%Genrates X, Y, Z (cartesian coordiantes of polar coordinates)
% INPUT: cubeSide:: size of 3d cubeSide
% OUTPUT: P:: X, Y, Z coordinates of the cone 1, 2 ,3
%         F:: how may polar point fall into same cartesian coordinates
function P=GeneratePyramidSection(cubeSide)
P=cell(1,4);
[P{1}.X,P{1}.Y,P{1}.Z]= GenerateXYZ(cubeSide);
% F{1}=PolFreq(cubeSide,P{1}.X,P{1}.Y,P{1}.Z);

P{2}.Y=P{1}.X;
P{2}.X=P{1}.Y;
P{2}.Z=P{1}.Z;
% F{2}=PolFreq(cubeSide,P{2}.X,P{2}.Y,P{2}.Z);

P{3}.Y=P{1}.Y;
P{3}.X=P{1}.Z;
P{3}.Z=P{1}.X;
% F{3}=PolFreq(cubeSide,P{3}.X,P{3}.Y,P{3}.Z);
