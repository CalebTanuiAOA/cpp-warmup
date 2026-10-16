# C++ Warm-Up

Eight questions to get comfortable in C++ before Olympiad training starts.
Everything lives in one file: **`warmup.cpp`**.

No tests, no autograder, no marks. Each question below shows the output your
program should produce — run yours and compare.

---

## Getting started

**1. Fork this repository** (button at the top right of the GitHub page), then
clone your fork:

```bash
git clone https://github.com/YOUR-USERNAME/cpp-warmup.git
cd cpp-warmup
```

**2. Build and run:**

```bash
g++ -std=c++17 -Wall -o run warmup.cpp && ./run
```

or just `./run.sh` if you prefer.

It already works before you change anything — run it first and look at the
worked example, which shows the house style.

**3. Work on one question at a time.** Write it, run it, check the output
against this page, then commit it:

```bash
git add warmup.cpp
git commit -m "Q1: count valid weights and track the longest run"
git push
```

A commit per question. Messages say *why*, as always — `q1` is not a commit
message.

---

## Before you start

Three things about C++ that will catch you out, because Python never did:

**Nothing starts at zero unless you say so.** `int total;` holds rubbish.
Write `int total = 0;`.

**`int` division throws the fraction away.** `7 / 2` is `3`. If you want a
real answer, make one side a decimal: `7 / 2.0`.

**`cout` shows 6 significant figures by default.** A total of `153945.75`
would print as `153946`. Where that matters below, the expected output shows
what you will actually see on screen.

Build with `-Wall` and read the warnings. A warning is the compiler telling
you about a bug it can see and you cannot.

---

# Core questions

Six questions. 

## Q1 · The weighing session

**Uses:** `morningWeights` · *vectors, loops, if, tracking state*

One morning's weights, in the order they were taken. Some are nonsense: the
scale was knocked, or nothing was on it.

A weight is **valid** if it is more than 0 and not more than 80.

Report four things:

1. the total of all twelve weights
2. how many are valid
3. the **heaviest weight in the list** and **which position it is at**,
   counting from 0 — note this may well be an invalid reading
4. the length of the longest unbroken run of consecutive valid weights

```
=== Q1 ===
Total: 487.5 kg
Valid: 9 of 12
Heaviest: 95 kg at position 7
Longest valid run: 3
```

> The run is the part worth thinking about. You need two counters: how long
> the current run is, and the best you have seen. An invalid weight resets one
> of them and not the other.

## Q2 · Grade summary

**Uses:** `logbook` · *structs, loops, if, accumulators, division*

For each grade A, B and C, report how many deliveries there were, their total
weight, and their average weight. Then say which grade had the best **average**.

```
=== Q2 ===
Grade A: 6 deliveries, 219.5 kg total, 36.5833 kg average
Grade B: 3 deliveries, 165 kg total, 55 kg average
Grade C: 2 deliveries, 62 kg total, 31 kg average
Best average: grade B
```

> Grade B wins on average while grade A wins on total. Those are different
> questions and they have different answers.
>
> Guard against dividing by zero. There happen to be deliveries of every grade
> in this data, but your code should not fall over if there were not.

## Q3 · Who is who

**Uses:** `logbook` · *structs, functions, searching, "not found"*

First write the function at the bottom of `warmup.cpp`:

```cpp
int findFarmer(const vector<Delivery> &log, string name);
```

It returns the position of that farmer's **first** delivery, or `-1` if they
are not in the log at all. Use it to look up `Isanda` and `Mukamana`.

Then answer two questions: who delivered the **most times**, and who delivered
the **most kilograms in total**?

```
=== Q3 ===
findFarmer(Isanda) = 2
findFarmer(Mukamana) = -1
Most deliveries: Keza (3)
Most kg: Onyinye (138.5 kg)
```

> Those two answers are different people. If you guess that the busiest farmer
> is also the biggest, this data will catch you.
>
> Returning `-1` for "not found" is a very common convention. Think about when
> it would be a bad idea.

## Q4 · Payment run with a daily cap

**Uses:** `logbook` · *functions, if chains, state carried across a loop*

Write the other function at the bottom of the file:

```cpp
double payment(double kg, char grade);
```

The rate is 450 per kg. Grade A earns 10% above it, grade B earns the rate,
anything else earns 20% below it.

**The cap:** the station only has so much cash. Once the amount paid out so far
**passes 100,000**, every payment after that is **halved**. Work through the
logbook in order, print what each farmer actually receives, mark the halved
ones, and print the final total.

```
=== Q4 ===
Keza 45.5 kg grade A -> 22522.5
Bonu 80 kg grade B -> 36000
Isanda 20 kg grade A -> 9900
Keza 12 kg grade C -> 4320
Onyinye 66.5 kg grade B -> 29925
Karimi 31 kg grade A -> 7672.5  (halved)
Karimi 31 kg grade A -> 7672.5  (halved)
Keza 18.5 kg grade B -> 4162.5  (halved)
Bonu 50 kg grade C -> 9000  (halved)
Isanda 20 kg grade A -> 4950  (halved)
Onyinye 72 kg grade A -> 17820  (halved)
Total paid: 153945
```

> You cannot work out any one payment on its own — it depends on everything
> paid before it. The order of the logbook matters, which is unusual and worth
> noticing.
>
> Check the moment the cap bites. After five deliveries the running total is
> 102,667.50, which is past 100,000 — so the sixth is the first to be halved.

## Q5 · The validation report

**Uses:** `rawRecords` · *structs, strings, several rules, first-failure reporting*

These are records as the volunteers typed them, before anyone checked them.
The weight is stored as **text**, because a person can type anything.

A record is acceptable when **all** of these hold:

| Field | Rule |
| --- | --- |
| `id` | the letter `F` followed by exactly three digits |
| `kg` | present, a number, more than 0 and not more than 80 |
| `grade` | `A`, `B` or `C` — capital letters do not matter |

Print each record as ACCEPT, or REJECT with **the first rule it broke**,
checking in the order of the table above. Then print the totals.
```
=== Q5 ===
F012 ACCEPT
F7 REJECT - bad id
F033 REJECT - weight not a number
F021 REJECT - weight out of range
F044 ACCEPT
F055 REJECT - weight missing
F066 REJECT - unknown grade
F077 REJECT - weight out of range
2 accepted, 6 rejected
```

> Your exact wording of the reasons does not matter; which record fails and
> why does.
>
> Two to look at. `F044` has grade `'b'` in lower case and is **accepted** —
> capitals do not matter. `F021` has weight `0`, which is a perfectly good
> number, in the right place, and still not allowed.
>
> Useful here: `isdigit(c)` tells you whether a character is a digit,
> `toupper(c)` makes a letter capital, and `stod(s)` turns text into a number —
> but only call `stod` once you know the text really is a number.

## Q6 · Igisoro: a full turn

**Uses:** `board` · *vectors, modular arithmetic, a loop whose condition depends on what just happened*

Your 16 pits, in sowing order. Sowing runs anticlockwise and wraps from pit 16
back round to pit 1. `board[1]` really is pit 1 — position 0 is unused, which
saves a lot of off-by-one headaches.

Play **pit 6**. Take every seed out of it and drop them one at a time into the
pits that follow. Then apply the relay rule:

- if the last seed lands in a pit that was **empty** (so it now holds exactly
  1), the turn ends
- if it lands in a pit that **already had seeds**, pick all of them up and keep
  sowing from there

Report the final board, which pit the last seed landed in, and how many laps it
took.

```
=== Q6 ===
Final board: 0 0 1 0 0 0 2 1 1 0 3 1 0 6 1 0 
Landed in pit 15 after 3 laps
```

> You wrote this as pseudocode in Week 1. The wrap-around is the same line:
> `current = (current % 16) + 1;`
>
> **The insight:** at the moment your last seed lands, how do you know whether
> that pit was empty *before*? You do not need to remember anything — after
> your seed is in, "was empty" and "now holds exactly 1" are the same statement.

---

# Stretch questions

Optional. They are uncommented at the
bottom of `warmup.cpp` — uncomment one if you get there.

## Q7 · Sort the logbook

**Uses:** `logbook` · *custom comparators, multi-key sorting*

Sort the logbook three ways and print each:

1. heaviest first
2. alphabetically by farmer
3. by grade (A, then B, then C) and, **within the same grade**, heaviest first

```
=== Q7 ===
Heaviest first: Bonu(80) Onyinye(72) Onyinye(66.5) Bonu(50) Keza(45.5) Karimi(31) Karimi(31) Isanda(20) Isanda(20) Keza(18.5) Keza(12) 
Alphabetical: Bonu Bonu Isanda Isanda Karimi Karimi Keza Keza Keza Onyinye Onyinye 
Grade then weight: AOnyinye(72) AKeza(45.5) AKarimi(31) AKarimi(31) AIsanda(20) AIsanda(20) BBonu(80) BOnyinye(66.5) BKeza(18.5) CBonu(50) CKeza(12) 
```

> `sort` can order numbers on its own. It cannot know whether one `Delivery`
> comes before another — you have to tell it, with a function that answers one
> question: *should a come before b?*
>
> ```cpp
> bool byWeight(const Delivery &a, const Delivery &b) {
>     return a.kg > b.kg;
> }
> sort(logbook.begin(), logbook.end(), byWeight);
> ```
>
> The third sort needs two keys: compare the grades, and **only when they are
> equal** fall back to comparing the weights.

## Q8 · Spotting double-entries

**Uses:** `logbook` · *nested loops vs a single pass*

Somebody typed a delivery into the logbook twice. Find records that look like
accidental double-entries — **same farmer, same weight. same grade** — under two different
definitions:

1. only when the two sit **next to each other** in the log
2. **anywhere** in the log

```
=== Q8 ===
Adjacent: Karimi(31) 
Anywhere: Isanda(20) at 2 and 9  Karimi(31) at 5 and 6
```

> The two definitions give different answers on the same data. Only one of
> those pairs is a genuine double-entry; Isanda really did bring 20 kg twice,
> hours apart. Which rule would you actually want, and what else would you need
> to record to tell the difference?
>
> The second part invites a loop inside a loop. That is fine for 11 records.
> Ask yourself what it would cost if the logbook held 100,000.

---

## When you are stuck

1. Read the compiler error from the **top**. The first one is real; the rest
   are often just confusion caused by the first.
2. Missing `;` at the end of a line? Missing `}`?
3. Print things out to see what is happening: `cout << x << "\n";`
4. Run the failing part by hand on paper, the way you have done trace tables
   all term. It works the same here.

## Submission
Submit the repo link to this [google form](https://docs.google.com/forms/d/e/1FAIpQLSeYDjXXHP4yP0RYl9Di-FW-fRQNDofKskJ4W_uOGFPcGd798w/viewform?usp=preview)