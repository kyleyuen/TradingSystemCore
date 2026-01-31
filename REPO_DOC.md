# PriceDataTracker — Repository Documentation

This document is intended to be passed to a reasoning model (e.g., ChatGPT) so it has full context on what each file is, what it does, how it behaves, and where potential issues or assumptions lie.

---

## Project Summary
PriceDataTracker is a small C++ program to read price data from a CSV file and track simple statistics (recent price, highest price, lowest price, and per-row prices). It uses a `PriceData` container and a `readCSV` helper to parse CSV files and populate the data.

---

## Files (per-file descriptions)

### `main.cpp` ✅
- Purpose: CLI entry point used to read a CSV file (provided as `argv[1]`), populate a `PriceData` instance using `readCSV`, and print a short summary for quick testing.
- Key behavior:
  - Validates that a filename was passed; if not, prints an error and returns `-1`.
  - Creates `PriceData priceData;` and `readCSV reader;`.
  - Calls `reader.readData(argv[1], priceData)`; on failure prints error and returns `-1`.
  - On success, prints:
    - "Successfully read CSV file: <filename>"
    - `Recent price`, `Highest price`, `Lowest price`
    - `Sample prices` for the first 5 timestamps (if present)
  - Returns `0` on success.
- Usage example: `./tracker 6758_jp_d.csv`

### `PriceDataTracker.h` ✅
- Purpose: Declares the `PriceData` class and its public interface.
- Public API (signatures):
  - `PriceData();` — constructor
  - `double price(int time);` — returns price for specific timestamp (ms or index), or `-1` on error/not-found
  - `double highestPrice();` — returns highest observed price, or `-1` if no data
  - `double lowestPrice();` — returns lowest observed price, or `-1` if no data
  - `double recentPrice();` — returns the most recent price (the one associated with the largest timestamp), or `-1` if no data
  - `bool addPrice(int time, double amount);` — add/update a price for a timestamp; returns `false` on invalid input (e.g., negative price), `true` on success
- Internal state (fields):
  - `std::unordered_map<int,double> data;` — stores prices by integer timestamp
  - `double latestPrice;` and `int latestTimestamp;`
  - `double HPrice;` (highest), `double LPrice;` (lowest)
  - `bool state;` — indicates whether any valid data exists

### `PriceDataTracker.cpp` ✅
- Purpose: Implements `PriceData` behaviour.
- Notes on implementation:
  - Constructor: sets `state = false` (no data yet).
  - `price(time)`: returns `-1` if `state` is false or timestamp missing; else returns `data[time]`.
  - `highestPrice()`, `lowestPrice()`, `recentPrice()`: return `-1` if `state` false, else their respective values.
  - `addPrice(time, amount)`:
    - Returns `false` if `amount < 0`.
    - If first data point (state false): initializes `latestTimestamp`, `HPrice`, `LPrice`, `latestPrice` and sets `state = true`.
    - If `time` > `latestTimestamp`, updates `latestTimestamp` and `latestPrice`.
    - Adjusts `HPrice` and `LPrice` as needed.
    - Stores/update `data[time] = amount`.
    - Returns `true` on success.
  - Note: The function overwrites existing timestamps (no explicit check to block duplicates).

### `ReadCSV.h` ✅
- Purpose: Declares `readCSV` helper class used to parse CSV and fill a `PriceData` instance.
- Important: Uses a forward declaration `class PriceData;` to avoid including the full header in the interface.
- Public API:
  - `readCSV();` — constructor
  - `bool readData(const char* filename, PriceData& priceData);` — parses file and populates `priceData`; returns `true` on success, `false` on failure (e.g., file open error)

### `readCSV.cpp` ✅
- Purpose: Implements CSV parsing and `readData`.
- Behavior details:
  - Opens file using `std::ifstream dataFile(filename)`; returns `false` if not opened.
  - Reads and discards the first line (header) via `getline`.
  - Loops through remaining lines, splitting each line by comma using `std::stringstream`.
  - Extracts the closing price from column index `4` (i.e., the 5th column; indexing starts at 0).
  - Uses `stod(feild)` to convert the extracted field into a `double` (note: can throw `std::invalid_argument` if malformed).
  - Calls `priceData.addPrice(rows, closePrice);` using `rows` (an integer line counter) as the timestamp.
  - Increments `rows` per data row.
  - Returns `true` at the end when parsing completes.
- Assumptions and caveats:
  - The CSV has a header line.
  - The closing price is in the 5th column (column index `4`). If the CSV format differs this will be incorrect.
  - There is no try/catch around `stod`: malformed numeric fields will cause an exception.
  - The timestamp used is the row index (0-based). If you want real timestamps, modify `readData` accordingly.

### `Makefile` ✅
- Purpose: Simple build helper.
- Usage:
  - `make` — builds `tracker` (the default target)
  - `make clean` — removes object files and `tracker`
- Implementation:
  - Compiler flags: `-std=c++11 -O2 -Wall -Wextra`
  - Sources: `main.cpp`, `PriceDataTracker.cpp`, `readCSV.cpp`

### `6758_jp_d.csv` (sample data) ✅
- Purpose: Example CSV included to allow immediate testing.
- Observed output when running `./tracker 6758_jp_d.csv` from the current repo:
  - `Recent price: 3432`
  - `Highest price: 4700`
  - `Lowest price: 146.171`
  - Sample first five `t=0..4` prices: `1047.14`, `1082.98`, `1110.75`, `1107.16`, `1074.91`.

### Git files
- `.git/` — Git repository data (commits, refs, etc.).

---

## Build & Run (quick)
1. Build: `make` or `g++ main.cpp PriceDataTracker.cpp readCSV.cpp -std=c++11 -O2 -Wall -Wextra -o tracker`
2. Run: `./tracker <path-to-csv>` (example: `./tracker 6758_jp_d.csv`)
3. Exit codes: `0` on success, `-1` if input/reading errors occurred.

---

## Known issues & suggested checks (for a reasoning model)
- CSV parsing assumes the closing price is at column index 4; if your CSV differs, update `readCSV.cpp`.
- `stod` is not guarded: malformed numeric strings will throw exceptions and crash the program.
- `PriceData::price(int time)` uses `-1` as an error sentinel; that conflicts with valid negative prices (if negative prices are valid in your domain). Currently `addPrice` disallows negative prices.
- Duplicate timestamps are allowed and will overwrite existing values without warning.
- Timestamps used are simple row indices (0..N-1). If you expect time-based ms timestamps, adjust `readCSV` to parse the appropriate column and pass that value to `addPrice`.

---

## Recent edits (what changed since import)
- Fixed an incorrect method declaration in `ReadCSV.h` (removed incorrect qualification).
- Added `return true;` to `PriceData::addPrice` implementation so the function returns a value.
- Enhanced `main.cpp` to print file summary and sample prices for quick testing.
- Added `Makefile` for convenient `make` / `make clean` usage.
- All edits were committed and pushed to `https://github.com/kyleyuen/TradingSystemCore.git` on branch `main`.

---

If you want this formatted differently or need more details (e.g., a JSON schema, a per-function example of input/output, or explicit AST-style signatures for each function), tell me how you want it structured and I'll update `REPO_DOC.md` accordingly.
