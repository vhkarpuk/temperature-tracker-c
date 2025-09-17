# 🌡️ Temperature Tracker (C Project)

A simple **command-line tool in C** to record and analyze daily temperatures.  
Built as part of a programming foundations portfolio to practice **arrays, pointers, loops, and menu-driven logic**.

---

## 📌 Features
- Record up to **30 daily temperatures** (with early stop using `-1`)
- Display all readings with **pointer traversal**
- Calculate **average temperature**
- Find **highest and lowest** values with day index
- Count days **above/below a threshold**
- Compute **weekly averages** (7-day blocks, including partial weeks)
- Reverse the order and display readings as *Today / Yesterday / X days ago*
- Menu-driven interface for easy interaction

---

## 🛠️ Compilation & Usage

Make sure you have `gcc` installed.  
Clone the repository and compile the program:

```bash
gcc temperature-tracker-c.c -o temp_tracker
./temp_tracker
