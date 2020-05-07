#!/bin/bash
../configure \
  --prefix="$HOME/ffmpeg_build" \
  --enable-shared \
  --disable-static \
  --enable-librtmp \
  --extra-libs=-lpthread \
  --extra-libs=-lm \
  --enable-gpl \
  --enable-libfreetype \
  --enable-libmp3lame \
  --enable-libopus \
  --enable-libvorbis \
  --enable-libtheora \
  --enable-libvpx \
  --enable-libx264 \
  --enable-libx265 \
  --enable-nonfree \
  --enable-libfdk_aac \
  #--enable-libass \
#  --enable-cuda \
#  --enable-cuvid \
#  --enable-nvenc \
#  --enable-nonfree \
#  --enable-libnpp
#make
#make install
