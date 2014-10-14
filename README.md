Image processing toolbox
==============================

Requirements
---------------------------
* Boost
* OpenCV
* Qt

How to build
---------------------------

```bash
$> cd Build
```

```bash
$>vi scripts/MCONFIG.local
```

edit the paths for Qt, opencv and boost if they are not installed in the standard parhs

```bash
$> make
```

Features
-------------------------
* The algorithms implemented can be listed when application is started
* Currently only console based application available
* GUI and Web interface will be added later
* I have implemented a MVC plugin interface. The controller detect which algorithms are implemented at runtime and requests the view to generates a display accordingly. This makes adding algorithms trivial as no change has to be made to the controller or view. The model library can be changed removed without having to recompile the controller or view.

List of Algos
-----------------------
* Scaling (biliniar)
* Gradient(sobel scharr DoG)
* Threshold(binary bitsplice)
* Enhancements(normalization)
* Spatial(Gaussian)

