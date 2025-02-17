# dc-template

Trying to reproduce issue with gl rotation.
When using raylib, I observed that the rotation is very slow. The issue is in fact with GL library.
On old version of kos / kos-ports, the rotation is working properly. (snapshot from 27JUL24)

# Report

## First tests 

- maishuji/dc-kos-image:14.1.1_01FEB25 : Rotation is broken (very slow);
- maishuji/dc-kos-image:14.1.1_08OCT24 : Rotation is broken (very slow);
- maishuji/dc-kos-image:14.1.1_27JUL24 : Rotation works properly (this image was build roughly at the same time, meaning it used GCdc from around 27JUL24, whereas others were build fetching master branch of GLdc)
- maishuji/dc-kos-image:14.1.1_21AUG24 : Rotationg is broken

## Change of strategy

As it is probably coming from GLdc, I have build different image with diferent GLdc snapshots. (The kos and kos-ports snapshot used are the same)
I have build the image with the following GLdc snapshots:

| docker image | description | observation |
|--- |--- | --- |
| maishuji/dc-kos-image:14.1.1_27JUL24-gl27JUL24 | kos for 27JUL24, with GLdc from 27JUL24 | Rotation works properly | 
|maishuji/dc-kos-image:14.1.1_27JUL24-gl11AUG24 | kos for 27JUL24, with GLdc from 11AUG24 | Rotation is broken (very slow)|
|maishuji/dc-kos-image:14.2.1-dev-latest-gl11aug24| kos + kos-ports from master, GLdc 11AUG24 | Rotation is broken (very slow) |
|maishuji/dc-kos-image:14.2.1-dev-latest-gl27jul24 | kos _ kos-ports from master, GLdc 27JUL24 | Rotation wokrs properly



# How to reproduce
1. Clone this repository
2. Use VS Code with Remote - Containers extension
3. Open the repository in the devcontainer ( defined in .devcontainer/devcontainer.json )
    choose the docker image (see above the one tested)
4. Build with cmake
    Delete build directory
    Ctrl + Shift + p -> choose reconfigure and delete cache
    Ctrl + Shift + p -> choose clean and rebuild
5. The cdi image is put in the out folder. Run it with a emulator (i' m using flycast) or dc-tools-ip (the later not tested)
