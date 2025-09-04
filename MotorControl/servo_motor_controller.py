# servo_motor_controller.py
# Model of PID Controller for Servo Motor 
# Output: step responce plot, Bode plot, and print gain/phase margins.

import matplotlib.pyplot as plt
import numpy as np
import control as ctl

# Laplace variable
s = ctl.TransferFunction.s

# Model Parameters
J  = 0.01     # Inertia of motor and load (kg·m^2)
b  = 0.001    # Damping coefficient (N·m·s/rad)
Kt = 0.10     # Motor torque constant (current -> torque) (N·m/A)
Kp = 0.005    # Proportional PID constant
Ki = 1.56e-4  # Integral PID constant
Kd = 0.05     # Derivative PID constant

# Transfer Functions 
Gp = 1 / ( s * (J*s + b) )      # Plant (torque -> position)
Gc = Kp + Ki/s + Kd*s           # PID Controller (error -> current)
G = Gc * Kt * Gp                # Open loop Xfer func (error -> position)
T = ctl.feedback(G)             # Closed loop Xfer func (position command -> position output)
S = ctl.minreal(1/(1+G))        # Sensitivity

# Stability Margins
gm, pm, wg, wp = ctl.margin(G)

# Convert gain margin to dB if finite
gm_db = 20*np.log10(gm) if np.isfinite(gm) and gm > 0 else np.inf

# Print Stability Margins
print("=== Stability Margins ===")
print(f"Gain margin:  {gm:.3g} ({gm_db:.2f} dB) at ω = {wg:.3g} rad/s")
print(f"Phase margin: {pm:.2f}° at ω = {wp:.3g} rad/s")
print("\n=== Plant ===")
print(Gp)
print("\n=== PID Controller ===")
print(Gc)
print("\n=== Open Loop TF ===")
print(G)

# Step Response (closed loop)
t, y = ctl.step_response(T)
plt.figure()
plt.plot(t, y)
plt.xlabel("Time [s]")
plt.ylabel("Position [rad]")
plt.title("Closed-loop Step Response")
plt.grid(True)

# Bode Plot (open loop)
plt.figure()
ctl.bode(G, dB=True, Hz=False)
plt.suptitle("Open-loop Bode Plot")
plt.show()
