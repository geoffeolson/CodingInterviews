# servo_motor_controller.py
# Model of PID Controller for Servo Motor
# Outputs: step response plot, Bode plot, pole–zero maps, root locus, and stability metrics.

import matplotlib.pyplot as plt
import numpy as np
import control as ctl

# ------------ Settings -------------
SAVE_FIGS = False   # set True to save PNGs alongside showing them
# -----------------------------------

# Laplace variable
s = ctl.TransferFunction.s

# Model Parameters
J  = 0.01     # Inertia of motor and load (kg·m^2)
b  = 0.001    # Damping coefficient (N·m·s/rad)
Kt = 0.10     # Motor torque constant (current -> torque) (N·m/A)

# PID gains (ideal derivative; swap to filtered derivative if needed)
Kp = 0.005
Ki = 1.56e-4
Kd = 0.05
# Optional derivative filter:
# tau_d = 0.2
# Gc = Kp + Ki/s + (Kd*s)/(1 + tau_d*s)

# Transfer Functions
Gp = 1 / ( s * (J*s + b) )      # Plant (torque -> position)
Gc = Kp + Ki/s + Kd*s           # PID (error -> current); use filtered form above if desired
G  = Gc * Kt * Gp               # Open-loop TF (error -> position)
T  = ctl.feedback(G)            # Closed-loop TF (command -> position)
S  = ctl.minreal(1/(1+G))       # Sensitivity

# --- Stability Margins (open loop) ---
gm, pm, wg, wp = ctl.margin(G)
gm_db = 20*np.log10(gm) if np.isfinite(gm) and gm > 0 else np.inf

print("=== Stability Margins (Open Loop) ===")
print(f"Gain margin:  {gm:.3g} ({gm_db:.2f} dB) at ω = {wg:.3g} rad/s")
print(f"Phase margin: {pm:.2f}° at ω = {wp:.3g} rad/s")

# --- Print TFs ---
print("\n=== Plant (Gp) ===")
print(Gp)
print("\n=== PID Controller (Gc) ===")
print(Gc)
print("\n=== Open Loop TF (G = Gc * Kt * Gp) ===")
print(G)

# --- Closed-loop poles/zeros + damping ratios ---
poles = ctl.pole(T)
zeros = ctl.zero(T)
print("\n=== Closed-loop Poles (with natural freq & damping) ===")
for k, p in enumerate(poles, 1):
    wn = abs(p)                 # natural frequency [rad/s]
    zeta = -np.real(p)/wn if wn > 0 else np.nan
    print(f"p{k}: {p:.6g}   | wn={wn:.4f} rad/s, zeta={zeta:.4f}")
print("\n=== Closed-loop Zeros ===")
print(zeros if len(zeros) else "None")

# --- Step-response summary ---
try:
    info = ctl.step_info(T)
    print("\n=== Step Info (Closed Loop) ===")
    for k, v in info.items():
        print(f"{k}: {v}")
except Exception:
    # step_info may not exist in some older versions
    pass

# --- Step Response (closed loop) ---
t, y = ctl.step_response(T)
plt.figure()
plt.plot(t, y)
plt.xlabel("Time [s]")
plt.ylabel("Position [rad]")
plt.title("Closed-loop Step Response")
plt.grid(True)

# --- Pole–Zero Plot (closed loop) ---
plt.figure()
try:
    ctl.pzmap(T, Plot=True)
    plt.title("Closed-loop Pole–Zero Map")
except Exception:
    from control.matlab import pzmap as ml_pzmap
    ml_pzmap(T, grid=True)
    plt.title("Closed-loop Pole–Zero Map (ζ–ω grid)")

# --- Pole–Zero Plot (open loop; optional insight) ---
plt.figure()
try:
    ctl.pzmap(ctl.minreal(G), Plot=True)
    plt.title("Open-loop Pole–Zero Map (minreal)")
except Exception:
    from control.matlab import pzmap as ml_pzmap
    ml_pzmap(ctl.minreal(G), grid=True)
    plt.title("Open-loop Pole–Zero Map (minreal, ζ–ω grid)")

# --- Root Locus (open loop with scalar gain K) ---
plt.figure()
try:
    ctl.rlocus(G)   # varies a scalar K multiplying G
except Exception:
    from control.matlab import rlocus as ml_rlocus
    ml_rlocus(G)
plt.title("Root Locus of Open-loop G(s)")

# --- Bode Plot (open loop) ---
plt.figure()
ctl.bode(G, dB=True, Hz=False)
plt.suptitle("Open-loop Bode Plot")

# --- Save figures (optional) ---
if SAVE_FIGS:
    # Figures created in order: 1=step, 2=pz_closed, 3=pz_open, 4=rlocus, 5=bode
    names = ["step", "pz_closed", "pz_open", "root_locus", "bode"]
    for i, name in enumerate(names, start=1):
        plt.figure(i)
        plt.savefig(f"{name}.png", dpi=200, bbox_inches="tight")

plt.show()
