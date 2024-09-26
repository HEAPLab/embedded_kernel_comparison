#!/usr/bin/env bash
if [[ "$0" == *"setenv.sh"* ]]; then
  echo To add the toolchains to the path execute:
  echo '  source setenv.sh'
else
  echo Adding the toolchains to the path.
  export PATH="$(readlink -f -- $(dirname -- ${BASH_SOURCE[0]}))/toolchain_freertos/bin:$PATH"
  export PATH="$(readlink -f -- $(dirname -- ${BASH_SOURCE[0]}))/toolchain_linux/bin:$PATH"
  export PATH="$(readlink -f -- $(dirname -- ${BASH_SOURCE[0]}))/toolchain_miosix/bin:$PATH"
fi
