set windows-shell := ["C:/Program Files/Git/bin/bash.exe", "-euo", "pipefail", "-c"]
set script-interpreter := ["C:/Program Files/Git/bin/bash.exe", "-euo", "pipefail"]

newup DAY:
    if [ -f ./day{{ DAY }}.h ]; then \
        echo "Day {{ DAY }} already exists"; \
    else \
        sed s/X/{{ DAY }}/g dayX.h > day{{ DAY }}.h; \
        sed s/X/{{ DAY }}/g dayX.c > day{{ DAY }}.c; \
        sed s/X/{{ DAY }}/g Inputs/dayX.h > Inputs/day{{ DAY }}.h; \
        git add .; \
    fi
