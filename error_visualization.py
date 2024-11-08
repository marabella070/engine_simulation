import pandas as pd
import matplotlib.pyplot as plt
import argparse

# Handling command line arguments
parser = argparse.ArgumentParser(description="Plot Torque vs Crankshaft Speed from CSV files")
parser.add_argument("original_file", help="Path to the original data CSV file")
parser.add_argument("simulation_file", help="Path to the simulation data CSV file")
args = parser.parse_args()

# Loading data from files
original_data = pd.read_csv(args.original_file)
simulation_data = pd.read_csv(args.simulation_file)

# Plotting
plt.plot(original_data["Speed"], original_data["Torque"], label="Original Data")
plt.plot(simulation_data["Speed"], simulation_data["Torque"], label="Simulated Data", linestyle='--')

plt.xlabel("Crankshaft Speed (rpm)")
plt.ylabel("Torque (Nm)")
plt.legend()
plt.title("Torque vs Crankshaft Speed")
plt.show()