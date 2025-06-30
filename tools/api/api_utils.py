# Copyright 2025 The Lynx Authors. All rights reserved.
# Licensed under the Apache License Version 2.0 that can be found in the
# LICENSE file in the root directory of this source tree.

# /usr/bin/env python3
# -*- coding: utf-8 -*-

import os
import re
import subprocess
import sys
import shutil
from env_setup import DOXYGEN_PATH, HANDLE_FAILED_INSTRUCTION


def remove_dirs(dir_path):
    """Remove all directories under the specified path
    Args:
        dir_path (str): Path to the directory
    """
    if os.path.exists(dir_path) and os.path.isdir(dir_path):
        try:
            shutil.rmtree(dir_path)
        except Exception as e:
            print(f"Failed to remove directory {dir_path}: {e}", file=sys.stderr)

def remove_and_create_dir(dir_path):
    remove_dirs(dir_path)
    os.makedirs(dir_path, exist_ok=True)


def is_doxygen_installed():
    """Check if doxygen is installed in the system

    Returns:
        bool: True if installed, False otherwise
    """
    try:
        subprocess.check_output([DOXYGEN_PATH, "--version"])
        return True
    except (subprocess.CalledProcessError, FileNotFoundError):
        print(
            f"Doxygen not found, please check {HANDLE_FAILED_INSTRUCTION} for more infomation",
            file=sys.stderr,
        )
        return False


def camel_to_kebab_regex(s):
    if not s:
        return s
    words = re.findall(r"[A-Z]?[a-z]+|[A-Z]+(?=[A-Z][a-z]|\b)", s)
    return "-".join(word.lower() for word in words)