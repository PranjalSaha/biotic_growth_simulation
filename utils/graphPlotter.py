#!/bin/python3

import matplotlib.pyplot as plt
import pandas as pd

# Read data from CSV file
filename = input("Enter filename : ")
filepath = "../results/" + filename
df = pd.read_csv(filepath)  # Read space-separated values
respath = "../results/" + filename.split('.')[0]


# Plot 1: Total Bacteria and Alive Bacteria vs. Time
plt.figure(figsize=(16, 12))
plt.plot(df["TimeElapsed"], df["AliveBacteria"], label="Alive Bacteria", 
         marker="o", linewidth=1)
plt.plot(df["TimeElapsed"], df["TotalBacteria"], label="Total Bacteria", 
         marker="s", linewidth=1)
plt.xlabel("Time Elapsed")
plt.ylabel("Bacteria Count")
plt.title("Total and Alive Bacteria vs. Time Elapsed")
plt.legend()
plt.grid()
filename = respath+"-bacteria.png"
plt.savefig(filename)
print("File successfully saved : " + filename)

# Plot 2: Total Nutrient vs. Time
plt.figure(figsize=(8, 6))
plt.plot(df["TimeElapsed"], df["TotalNutrient"], label="Total Nutrient", 
         color="green", marker="o", linewidth=1)
plt.xlabel("Time Elapsed")
plt.ylabel("Total Nutrient Level")
plt.title("Total Nutrient Level vs. Time Elapsed")
plt.grid()
filename = respath+"-nutrient.png"
plt.savefig(filename)
print("File successfully saved : " + filename )

# Plot 3: Net CO2 vs. Time
plt.figure(figsize=(8, 6))
plt.plot(df["TimeElapsed"], df["NetCO2"], label="Net CO2", color="red", 
         marker="o", linewidth=1)
plt.xlabel("Time Elapsed")
plt.ylabel("Net CO2 Level")
plt.title("Net CO2 Level vs. Time Elapsed")
plt.grid()
filename = respath+"-co2.png"
plt.savefig(filename)
print("File successfully saved : " + filename )
