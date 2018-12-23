#!/bin/bash
git submodule init
git submodule update
git pull --recurse-submodules
git submodule update --init --remote --recursive
