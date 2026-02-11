# PriceDataTracker

[![Language](https://img.shields.io/badge/C%2B%2B-11-00599C.svg)](https://en.cppreference.com/) [![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-blue.svg)](https://github.com/kyleyuen/PriceDataTracker) [![License](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/kyleyuen/PriceDataTracker/blob/main/LICENSE)

## 🎯 Project Overview

A high-performance C++ application for reading price data from CSV files and tracking key financial statistics. This project demonstrates proficiency in systems programming, data structures, CSV parsing, and technical analysis implementation. It serves as the foundation for a larger trading system with extensible indicator and signal architecture.

### 🎯 Purpose

Developed as a portfolio project to showcase skills in C++ development, file I/O operations, data structure optimization, and financial data analysis. Ideal for understanding efficient price tracking systems, indicator computation, and modular architecture design for trading applications.

## ✨ Features

### Core Functionality
- 📊 **Price Tracking**: Track price data with O(1) lookup by timestamp
- 📈 **Statistical Analysis**: Calculate highest, lowest, and most recent prices in real-time
- 📁 **CSV Parsing**: Robust CSV file reading with proper error handling
- 🔄 **Extensible Architecture**: Modular design for adding new indicators and strategies
- 💾 **Efficient Storage**: Hash map-based storage for fast price lookups
- ✅ **Data Validation**: Input validation for prices and timestamps

### Technical Indicators
- 📊 **Simple Moving Average (SMA)**: Calculate SMA over configurable window sizes
- 🎯 **Signal Strategies**: Framework for implementing trading signal strategies (in development)

### Developer Experience
- ⚡ **Fast Compilation**: Optimized C++11 build with -O2 flag
- 🧪 **Built-in Tests**: Comprehensive test suite in main executable
- 📝 **Clear API**: Well-documented public interface for all classes
- 🛠️ **Easy Build**: Makefile for simplified compilation and testing

## 🛠️ Tech Stack

- **Language**: C++11 with modern STL
- **Build System**: GNU Make
- **Compiler**: G++ (GCC) with optimization flags
- **Data Structures**: unordered_map (hash map) for O(1) price lookups
- **File I/O**: Standard C++ streams (ifstream, stringstream)
- **Standard Library**: STL containers and algorithms
- **Platform**: Cross-platform (Linux, macOS, Windows)

## 🚀 Getting Started

### Prerequisites

Before running this application, ensure you have:
- **C++ Compiler**: G++ or Clang with C++11 support
- **Build Tools**: GNU Make
- **Operating System**: Linux, macOS, or Windows
- **Text Editor/IDE**: Any text editor (VSCode, CLion, etc.)

### Installation & Setup

1. **Clone the Repository**
   ```bash
   git clone https://github.com/kyleyuen/PriceDataTracker.git
   cd PriceDataTracker
   ```

2. **Build the Project**
   ```bash
   # Build with Makefile
   make

   # Or compile directly with g++
   g++ src/main.cpp src/PriceDataTracker.cpp src/readCSV.cpp src/Indicators.cpp src/SMATrendStrategy.cpp \
     -std=c++11 -O2 -Wall -Wextra -Iinclude -o build/tracker
   ```

3. **Verify Installation**
   ```bash
   # Run built-in tests
   ./build/tracker

   # Or using make
   make test
   ```

## 📖 Usage Guide

### Application Flow

1. **Run Tests**: Execute the program without arguments to run built-in tests
2. **Read CSV**: Provide a CSV filename to parse price data and display statistics
3. **Data Processing**: The program automatically extracts closing prices and computes statistics
4. **View Results**: Summary displays entry count, latest price, high/low prices

### Command Line Usage

```bash
# Run built-in tests
./build/tracker
./build/tracker --test

# Read and analyze CSV file
./build/tracker 6758_jp_d.csv

# Clean build artifacts
make clean
```

### Sample Output

```
CSV read successfully. Summary:
  entries: 252
  latest ts: 251, latest price: 1520.5
  high: 1845.3, low: 1420.2
```

### API Reference

#### PriceData Class

```cpp
class PriceData {
public:
  // Constructor
  PriceData();

  // Accessors
  double price(int time);           // Get price at timestamp, returns -1 if not found
  double highestPrice();            // Returns highest price observed, -1 if no data
  double lowestPrice();             // Returns lowest price observed, -1 if no data
  double recentPrice();             // Returns most recent price, -1 if no data

  // Mutators
  bool addPrice(int time, double amount);  // Add/update price, returns false if invalid
};
```

#### SimpleMovingAverage Class

```cpp
class SimpleMovingAverage {
public:
  // Constructor with window size
  SimpleMovingAverage(int N);

  // Calculate SMA
  double SMA(PriceData& priceData);  // Returns SMA over last N prices, -1 if insufficient data
};
```

#### readCSV Class

```cpp
class readCSV {
public:
  // Constructor
  readCSV();

  // Parse CSV file
  bool readData(const char* filename, PriceData& priceData);  // Returns true on success
};
```

### CSV File Format

The application expects CSV files with the following format:

```
Date,Open,High,Low,Close
2024-01-01,100.0,102.5,99.5,101.0
2024-01-02,101.0,103.2,100.8,102.5
...
```

**Important**: The closing price is expected at column index 4 (5th column).

## 🎯 Learning Outcomes

This project demonstrates proficiency in:
- **C++ Systems Programming**: Memory management, STL containers, and efficient algorithms
- **Data Structure Design**: Hash maps for O(1) lookups and performance optimization
- **File I/O Operations**: Robust CSV parsing with error handling
- **Financial Data Analysis**: Computing technical indicators from price data
- **Modular Architecture**: Extensible design for adding new features
- **Build Systems**: Makefile configuration and compilation management
- **Testing**: Built-in test suite for validation and debugging
- **Code Organization**: Clear separation of concerns and well-documented interfaces

## 🔮 Future Enhancements

### Planned Features
- [ ] **Additional Indicators**: Exponential Moving Average (EMA), RSI, MACD
- [ ] **Signal Strategies**: Complete SMA-based trend signal implementation
- [ ] **Real-time Data**: Support for live market data feeds
- [ ] **Database Integration**: Store analysis results in SQLite/PostgreSQL
- [ ] **Performance Metrics**: Calculate Sharpe ratio, Sortino ratio, maximum drawdown
- [ ] **Data Export**: Export analysis results to CSV or JSON
- [ ] **Visualization**: Integration with plotting libraries
- [ ] **Multi-timeframe Analysis**: Analyze data at different time intervals

### Potential Improvements
- **Error Recovery**: Enhanced exception handling and recovery mechanisms
- **Logging System**: Detailed logging for debugging and monitoring
- **Configuration Files**: YAML/JSON config files for strategy parameters
- **Command-line Interface**: Argument parsing for flexible runtime configuration
- **REST API**: Expose functionality through HTTP endpoints
- **Docker Support**: Containerization for easy deployment
- **Performance Profiling**: Memory and CPU usage analysis tools

## 📊 Technical Specifications

| Aspect | Details |
|--------|---------|
| **Language** | C++11 |
| **Compiler** | G++ with -std=c++11 -O2 |
| **Data Structure** | unordered_map (average O(1) lookup) |
| **Memory Model** | Stack allocation with STL containers |
| **Build Time** | < 2 seconds (typical) |
| **Runtime Performance** | < 100ms for typical CSV files |
| **CSV Parsing** | Row-based with column extraction |

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

### Development Guidelines
1. Follow existing code style and conventions (C++11 standard)
2. Use meaningful variable names and add comments for complex logic
3. Test thoroughly with built-in test suite before submitting
4. Update documentation and REPO_DOC.md as needed
5. Ensure code compiles without warnings using the provided Makefile

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/kyleyuen/PriceDataTracker/blob/main/LICENSE) file for details.

## 👨‍💻 Author

**Kyle Yuen**
- GitHub: [@kyleyuen](https://github.com/kyleyuen)
- Project Link: [PriceDataTracker](https://github.com/kyleyuen/PriceDataTracker)
- Trading System Core: [TradingSystemCore](https://github.com/kyleyuen/TradingSystemCore)

## 🙏 Acknowledgments

- Inspired by modern quantitative trading systems
- Built as a learning exercise in C++ systems programming
- Thanks to the C++ standards committee and community
- Special thanks to the open-source community for continuous inspiration

---

⭐ **Star this repository if you found it helpful!** ⭐

**Last Updated**: February 2026
