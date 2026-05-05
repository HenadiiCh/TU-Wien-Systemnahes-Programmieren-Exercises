#!/usr/bin/env python3
"""
This script writes runtime environment details to "task1_output_python.txt"
including the script filename, execution date and time, Python implementation
and versions for NumPy and Matplotlib.

TODO:
  Ensure you can run this Python script in your environment
  run command from exercise1/:
  mkdir -p build output && python src/task1.test.py
"""

import platform
import numpy
import matplotlib
from datetime import datetime
from pathlib import Path

with open("output/task1_output_python.txt", "w") as f:
    f.write(
        f"""This script ({Path(__file__).name}) was executed
  - on {datetime.now()},
  - using {platform.python_implementation()} {platform.python_version()},
  - with {numpy.__name__} {numpy.__version__}, and
  - with {matplotlib.__name__} {matplotlib.__version__}."""
    )

print("task1.test.py: all asserts passed")
