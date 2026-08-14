<div align="center">

# 🎓 42_EXAM

### All 42 exams auto-corrected, ready to practice.

**ExamRank02 · 03 · 04 · 05 · 06** &nbsp;·&nbsp; **PiscineExam**

![Version](https://img.shields.io/badge/version-2.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux-lightgrey.svg)
![License](https://img.shields.io/badge/license-Apache%202.0-green.svg)

> 42_EXAM is now part of **[GRADEME.FR](https://grademe.fr)** 😎

</div>

---

## 📚 Table of Contents

- [✨ Features](#-features)
- [🖼 Screenshots](#-screenshots)
- [🚀 Quick Start](#-quick-start)
- [🎮 Cheat Codes](#-cheat-codes)
- [🕶 VIP Cheat Codes](#-vip-cheat-codes)
- [🤝 Contributing](#-contributing)
- [🔒 Privacy & GDPR](#-privacy--gdpr)
- [📄 Disclaimer](#-disclaimer)

---

## ✨ Features

- [x] New subjects — ExamRank02 (April 2022)
- [x] Subject drawn at random
- [x] Exponential waiting before correction
- [x] Timed sessions (X hours maximum)
- [x] Automatic correction — fully offline
- [x] Traceback available for each test
- [x] Infinite loop detection (ExamRank02)
- [ ] Infinite loop detection for all ExamRanks
- [ ] Memory leak detection for all exercises

> ⚠️ Works on **macOS and Linux** — the real exam runs on **Linux**.

---

## 🖼 Screenshots

![Grademe — exam session](https://user-images.githubusercontent.com/55356071/153122308-7a6c5a90-bc58-490b-b815-c4db6bc9bcdc.png)

![Grademe — project tests](https://user-images.githubusercontent.com/55356071/153124244-f2348ee5-16d0-4e73-b3f9-757638196996.png)

---

## 🚀 Quick Start

> ⚠️ The old one-liner `bash -c "$(curl https://grademe.fr)"` **no longer works** — `grademe.fr` now serves the web app (HTML), not the installer script.

Clone and launch **42_EXAM** from the repository:

```bash
git clone https://github.com/JCluzet/GrademeBash 42EXAM
cd 42EXAM
make          # start the exam
```

Available `make` commands:

```bash
make          # start the exam
make re       # restart from scratch
make help     # show available commands
```

> Visit [Grademe.fr](https://grademe.fr) to practice in the browser.

---

## 🎮 Cheat Codes

> ⚠️ *Sorry, these don't work during the real exam at 42.*

| Code | Effect |
|------|--------|
| `remove_grade_time` | Removes the waiting time between two submissions. The max exam duration becomes purely informational — an exercise can always be corrected, even past the time limit. |
| `force_success` | Forces an exercise to pass. |
| `new_ex` | Generates a new exercise at the same level. |

---

## 🕶 VIP Cheat Codes

Become a VIP by [sponsoring on GitHub](https://github.com/sponsors/JCluzet) or by [contributing to the project](CONTRIBUTING.md).

| Code | Effect |
|------|--------|
| `gradenow` | Instant correction — no grademe cooldown. |

> Being a sponsor brings VIP status to **GradeMe** and **42_EXAM**.
>
> VIPs get the exact same display as the 42 examshell. More features coming soon.

---

## 🤝 Contributing

You can contribute by adding new exercises or improving the program.

1. Read the [Contribution Guide](CONTRIBUTING.md).
2. Submit your exercise via a pull request.
3. If accepted, your name is listed below. 🥳

**Contributors:** `pandaero` · `Kuninoto` · `ComlanGiovanni`

Found a broken test? Open an **Issue** — it only takes 3 minutes and helps everyone.

---

## 🔒 Privacy & GDPR

Some data may be collected solely to improve the service (e.g. to determine whether an error comes from the student or the program). This data may include:

- The hostname of your machine
- The exam number you choose
- The exercise name, pass/fail status, current assignment, and level

---

## 📄 Disclaimer

> This project is **not** made by 42 School, is **not** identical to the official exams, and does **not** reflect the real exam at 42.

42_EXAM is built with the sole purpose of helping students understand their mistakes and improve. It works by running a `DIFF` between the student's rendering and the reference solution. All subjects are found on GitHub.

This project has only a **non-lucrative and educational purpose** — it is completely **free and open-source**.

---

<div align="center">

#### Your help is welcome 👋

*Remember: if you hit an error, you're probably not alone — your Issue will help others too.*

[Apache License 2.0](LICENSE)

</div>
