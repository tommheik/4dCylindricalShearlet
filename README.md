# 4dCylindricalShearlet
## 4d Cylindrical Shearlet Transform, Inverse and Adjoint for Matlab

**Detailed construction and numerical tests in**:  
T. A. Bubba, G. Easley, T. Heikkilä, D. Labate and J. P. Rodriguez Ayllon. "Efficient representation of spatio-temporal data using cylindrical shearlets" (2021). *Submitted*. Preprint: https://arxiv.org/abs/2110.03221

**Please cite the above article if you use these codes in your own projects.**

### Contents

**Root**: Readme and license files and the following 4 folders.

**main**: Simple test script `testMain.m` to try some of the properties, including forming the directional filters and computing forward, inverse and adjoint transforms of a simple 4d object. `hypercube.m` is a helper function for creating a semi-random 4d phantom. `cartoonPhantom.m` is the custom ellipsoid phantom used for the dynamic tomography tests.

**BP**: Short for bandpass, this folder contains the necessary routines and functions to perform the Laplacian pyramid decomposition and its inverse (reconstruction).

**dirFilters**: Contains the `GetMeyerBasedFilter.m` routine for creating the directional filters and all of the additional functions for splitting the Fourier domain to pyramids and sampling on polar and cartesian grids.

**4dCylShearTrans**: Contains the routines for the forward, inverse and adjoint transforms and the function `cylconv3d.m` which performs 3d cylindrical convolution using Fourier transform along the first 3 coordinates/components.

### Credits

**Decomposition, inverse and adjoint transforms, and extension of (pseudo)4d directional filters by Tommi Heikkilä.**

**This work is based on the 3d Cylindrical Shearlet implementation by Glenn Easley**:  
G. Easley, K. Guo, D. Labate and B. Pahari. "Optimally sparse representation of cartoon-like cylindrical data" (2020). *The Journal of Geometric Analysis*, pages 1-21.

**Generation of 3d Meyer-like directional filters by Pooran Negi, with contributions of D. Labate**:  
P. Negi and D. Labate. "3-d discrete shearlet transform and video processing" (2021). *IEEE transactions on Image Processing*, 21(6):2944-2954.

**Laplacian pyramid decomposition scheme is part of Surfacelet Toolbox for Matlab (SurfBox) by Yue Lu and Minh N. Do**:  
Y. M. Lu and M. N. Do. "Multidimensional Directional Filter Banks and Surfacelets" (2007). *IEEE Transactions on Image Processing*, 16(4):918-931.

**Extended array indexing function** `exindex.m` **by David Young**:  
D. Young. "Extended array indexing" (2010). *MATLAB Central File Exchange*, (https://www.mathworks.com/matlabcentral/fileexchange/27117-extended-array-indexing).

### ToDo

Some functions in dirFilters -folder are still missing their original authors.
