# CPE-3108
CPE 3108: Programming Project Adaptive Temperature and Hatch-Time Estimator Fish Egg Hatchery

A specialized command-line utility designed for fish hatchery management, providing precise estimates for egg hatching times based on environmental temperature using **Lagrange Interpolation**.

## 📌 Overview

The **Fish Hatchery Estimator** is a predictive tool developed for the CPE-3108 Programming Project. It addresses the variability in fish egg development by allowing hatchery managers to input species-specific datasets and calculate either:
1.  **Hatch-Time:** Estimated time to hatch based on a given temperature.
2.  **Temperature:** The required temperature to achieve a specific hatch-time.

By utilizing adaptive mathematical models, the system ensures that estimations are grounded in real data points, supporting both interpolation (within known ranges) and extrapolation (outside known ranges).

## ✨ Key Features

*   **Adaptive Estimation Logic:** Uses Lagrange polynomials to find the best fit for non-linear biological data.
*   **Proximity-Based Calculation:** Automatically selects the nearest data points to the input value to maximize accuracy.
*   **Dataset Management:**
    *   Create and save new species datasets.
    *   Load and manage existing records.
    *   Support for multiple data points per species.
*   **Detailed Calculation Breakdown:** The CLI provides a step-by-step visualization of the mathematical process, including the specific Lagrange basis polynomials ($L_i(x)$) used.
*   **Robust Input Handling:** Includes validation for numeric inputs and data point requirements.

## 🛠️ Technologies Used

*   **Language:** C
*   **Compiler:** GCC (GNU Compiler Collection)
*   **Mathematics:** Lagrange Interpolation & Polynomials
*   **Platform:** Windows (optimized for `.exe` execution)

## 🚀 Getting Started

### Prerequisites

*   A C compiler installed (e.g., [MinGW](https://www.mingw-w64.org/) for Windows).
*   Standard terminal or command prompt.

### Installation & Compilation

1.  Clone this repository:
    ```bash
    git clone https://github.com/ScarXiFy/CPE-3108.git
    ```
2.  Navigate to the `src` directory:
    ```bash
    cd CPE-3108/src
    ```
3.  Compile the source files using GCC:
    ```bash
    gcc -o hatch_estimator main.c displayfunc.c datafunc.c calculateLagrange.c
    ```

### Running the Application

After compilation, run the generated executable:
```bash
./hatch_estimator.exe
```

## 📖 Usage

1.  **Main Menu:** Select `1` to create a new dataset or `2` to load an existing one.
2.  **Creating Data:** Enter the species name and provide multiple temperature/time data points.
3.  **Calculating:** 
    *   Choose a species from the list.
    *   Select whether you want to calculate **Time** or **Temperature**.
    *   Input the number of data points to use for the calculation (at least 2).
    *   View the step-by-step mathematical derivation and the final result.
4.  **Help:** Select `3` from the main menu for detailed in-app instructions.

## 📂 Project Structure

*   `src/main.c`: Application entry point and menu loop.
*   `src/datafunc.c`: Handles dataset creation, loading, and memory management.
*   `src/calculateLagrange.c`: Core mathematical engine for interpolation and proximity sorting.
*   `src/displayfunc.c`: Manages CLI UI elements and formatting.
*   `src/main.h`: Shared structures and function prototypes.

## 🤝 Contributing

This project was developed as part of a Computer Engineering curriculum (CPE 3108). While primarily a student project, feedback and suggestions are welcome.

1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3.  Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
