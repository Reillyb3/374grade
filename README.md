# 374Grade
Quick project to estimate a user's grade in CS374.
# Setup:
Just clone this repository and run "make". Note that g++ must be installed for compilation to work. Also note that this is intended for Linux/Unix operating systems; if you're on Windows, I would recommend doing everything through WSL.
# Usage:
Copy [this google sheet](https://docs.google.com/spreadsheets/d/1_PtzEK_XwiY1K-ACZt27hoABpbF_mqrT8T4HYsznTqU/edit?usp=sharing) and fill blank fields corresponding to each problem and exam for which you have results. Then download as a csv, and run:
``grade_estimate [PATH TO CSV]``. As an example, your command should look something like ``grade_estimate sheet.csv``.
# What does it do?
This program calculates a student's score out of 100, where 100 is the highest grade achievable in this course. It first drops floor(15 * #(problems) / 36) homework problems (the same ratio of dropped homework as used for final grade calculation). It then uses the homework and exam scores to created a weighted current score (where assignments not yet graded are left as 0s). The same process is done for the class average scores, and the standard deviation is calculated to reflect this. Finally, the z-score for a student's current score out of 100, and the letter grade corresponding to it, are calculated and displayed.
# Disclaimers:
1. This program is extremely janky. If the csv given to it does not match the format it expects, it will break.
2. This is just for estimation; this program will overestimate your grade. This is because in actuality, the lowest problems being dropped for each student's grade will have the effect of raising the mean more than it is if the 2 problems with the lowest average are dropped.
