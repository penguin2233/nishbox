#!/bin/sh
ODE_VERSION=0.13

BASE=`pwd`

mkdir -p contrib
cd contrib

if [ ! -d ode-${ODE_VERSION} ]; then
	wget https://sourceforge.net/projects/opende/files/ODE/${ODE_VERSION}/ode-${ODE_VERSION}.tar.gz/download -O - | tar xvzf -
fi
cd ode-${ODE_VERSION}
if [ ! -f .configured ]; then
	./configure --host=${ARCH}-w64-mingw32 --prefix=$BASE/deps --disable-demos --without-drawstuff --enable-shared || exit 1
	touch .configured
fi
if [ ! -f .made ]; then
	${MAKE} -j4 || exit 1
	touch .made
fi
if [ ! -f .installed ]; then
	${MAKE} install
	touch .installed
fi
cd ..

cd ..

premake5 gmake2 --backend=opengl --opengl=wgl
${MAKE} config=release_win${BITS} -j4
