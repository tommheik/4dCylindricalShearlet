%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% function mBlock= PolarToRec(mRadialSlice,cubeSide,cPyramid)
%% Generates the XYZ coordinates of Polar Grid in Cartesian Grid
%% Input: mRadialSlice: 3-d Radial slice matrix
%%        cubeSide: order of block matrix in 3-d to be assembled
%%        cPyramid: cell containing one of 3 pyramid information
%% Output: 
%%        mBlock: block matrix in 3-d to be assembled
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function mBlock= PolarToRec(mRadialIdx,mRadial,cubeSide,cPyramid)
mBlock=zeros(cubeSide,cubeSide,cubeSide); 
for j=mRadialIdx(3,1):mRadialIdx(3,2)
  for i=mRadialIdx(1,1):mRadialIdx(1,2)
    for k=mRadialIdx(2,1):mRadialIdx(2,2)
      mBlock(cPyramid.X(i,k,j),cPyramid.Y(i,k,j),cPyramid.Z(i,k,j))=...
       +mRadial(i-mRadialIdx(1,1)+1, k-mRadialIdx(2,1)+1, j-mRadialIdx(3,1)+1);
    end
  end
end    
