Image processing toolbox
==============================

Requirements
---------------------------
* Boost
* OpenCV

How to build
---------------------------

```bash
$> cd Build

```bash
$>vi scripts/MCONFIG.local

edit the paths for opencv and boost if they are not installed in the standard parhs

```bash
$> make

Features
-------------------------
* The algorithms implemented can be listed when application is started
* Currently only console based application available
* GUI and Web interface will be added later 

List of Algos
-----------------------
Scaling (biliniar)
Gradient(sobel scharr DoG)
Threshold(binary bitsplice)
Enhancements(normalization)
Spatial(Gaussian)

