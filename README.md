# TU Wien: Systemnahes Programmieren - Exercises

![C++](https://img.shields.io/badge/C%2B%2B-17%2F20-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.15%2B-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

This repository contains a comprehensive collection of laboratory exercises for the **Systemnahes Programmieren** (Systems Programming) course at **TU Wien**. Each directory corresponds to a specific assignment, covering various aspects of low-level programming, C++ standards, and system-level concepts.

---

## 📂 Project Overview

| Exercise | Topic | Description |
| :--- | :--- | :--- |
| [**Ex 1**](./1/exercise1) | **Introduction** | Environment setup, basic C++ syntax, and CMake integration. |
| [**Ex 2**](./2/exercise2) | **Foundations** | Control structures, data types, and fundamental algorithms. |
| [**Ex 3**](./3/3/exercise3) | **Modularity** | Header-only libraries and project structuring. |
| [**Ex 4**](./4) | **Geometry & SVG** | 2D Geometry, transformation matrices, and SVG rendering. |
| [**Ex 5**](./5/5/exercise5) | **Logic** | Advanced algorithms and logical implementation in C++. |
| [**Ex 6**](./6/exercise6) | **OOP & Imaging** | Object-oriented design hierarchies and image processing. |
| [**Ex 7**](./7/exercise7) | **Modern C++** | C++20 Concepts, templates, and advanced type safety. |

---

## 🛠️ Building & Running

All exercises are built using **CMake**. Ensure you have a modern C++ compiler (GCC 11+, Clang 13+, or MSVC 2019+) and CMake installed.

### Standard Build Workflow

1.  **Navigate** to the desired exercise directory:
    ```bash
    cd 4
    ```
2.  **Configure** the project:
    ```bash
    cmake -B build
    ```
3.  **Build** the executable:
    ```bash
    cmake --build build
    ```
4.  **Run** the tests or application:
    ```bash
    ./build/exercise_name  # Path varies by exercise
    ```

> [!TIP]
> Use `cmake --build build -j` to speed up compilation using multiple CPU cores.

---

## 👤 Student Information

| Field | Detail |
| :--- | :--- |
| **Name** | Henadii Chalyi |
| **Student ID** | 12344365 |
| **University** | TU Wien |
| **Course** | Systemnahes Programmieren (182.721) |

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---
<p align="center">
  <i>Educational repository for academic purposes only.</i>
</p>
