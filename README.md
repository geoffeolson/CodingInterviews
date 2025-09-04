## Coding Interview

This repository contains sample questions and answers for coding interviews.

---

### Arrays

1. **Merge

   - Init
   - Con.

2. **Other**

   - For
   - Line

# PID Tuning Cheatsheet for a Servo with a Fast Current (Torque) Loop

> **Goal:** A practical, engineer-friendly recipe to pick **PID** gains for a **single outer position loop** when the drive’s **current loop is fast** (20 kHz class) so **torque ≈ proportional to current command**.

This file uses GitHub math ($…$, $$…$$). If any formulas don’t render, you can keep them as plain text.

---

## 1) Assumptions & Symbols

Inner **current loop** is tightly closed by the drive → torque follows command:
$$\tau(t) \approx K_t\, i_q^*(t)$$
In the outer loop we model an **effective torque gain** \(K_\tau\) (use \(K_\tau = K_t\) if your controller outputs current; otherwise fold it into the PID gains).
**Mechanical plant** about motor shaft with load reflected:
Inertia \(J\) [kg·m²], viscous damping \(b\) [N·m·s/rad]
Laplace variable \(s\), position \(\Theta(s)\), speed \(\Omega(s)\)

**Mechanical pole (no control):** \(\displaystyle \omega_m = \frac{b}{J}\) (rad/s)

---

## 2) Plant and Loop Definitions

**Torque → motion:**
\[
G_{\omega\tau}(s)=\frac{\Omega(s)}{\tau(s)}=\frac{1}{J s + b},\qquad
G_{\theta\tau}(s)=\frac{\Theta(s)}{\tau(s)}=\frac{1}{s(J s + b)}.
\]

**Controller (PID):**
- Ideal form:
\[
C_{\text{ideal}}(s)=K_p+\frac{K_i}{s}+K_d s = \frac{K_d s^2 + K_p s + K_i}{s}.
\]
- Practical derivative (noise-friendly):
\[
C(s)=K_p+\frac{K_i}{s}+\frac{K_d s}{1+\tau_d s}.
\]

**Open loop (unity feedback on position):**
\[
L(s)=C(s)\,K_\tau\,G_{\theta\tau}(s).
\]

**Closed-loop complementary sensitivity (command → position):**
\[
T(s)=\frac{\Theta(s)}{R(s)}=\frac{L(s)}{1+L(s)}.
\]

**Sensitivity (disturbance rejection, and error to reference):**
\[
S(s)=\frac{1}{1+L(s)}.
\]

**With ideal PID**, the denominators are explicitly:
\[
L_{\text{ideal}}(s)=\frac{K_\tau(K_d s^2 + K_p s + K_i)}{J s^3 + b s^2},
\]
\[
T_{\text{ideal}}(s)=\frac{K_\tau(K_d s^2 + K_p s + K_i)}{J s^3 + (b+K_\tau K_d)s^2 + (K_\tau K_p)s + (K_\tau K_i)}.
\]

**Stability margins** (Bode of \(L(j\omega)\)):
\[
\text{PM} = 180^\circ + \angle L(j\omega_{gc}),\qquad
\text{GM}_{\mathrm{dB}}=-20\log_{10}|L(j\omega_{pc})|.
\]
You want **PM > 0°** (typically 45–60°) and **GM > 0 dB** (≥ 6–10 dB).

---

## 3) One-Shot Tuning Recipe (Position loop only)

This shapes the loop so it looks like ~\(K/s\) at crossover → good damping.

**Step A — Add “velocity feedback”:** place the controller zero near the mechanical pole
\[
T_d \;\triangleq\; \frac{J}{b},\qquad K_d = K_p\,T_d.
\]
(With the derivative filter, this behaves like velocity feedback around crossover.)

**Step B — Pick a target crossover** \(\omega_c\).  
A safe starting range with the above zero is \(\omega_c \in [0.5,\,2]\,\omega_m\).  
Go higher for bandwidth if model/derivative are trustworthy.

**Step C — Set proportional gain by the unity-gain condition**
\[
\boxed{K_p = \frac{b\,\omega_c}{K_\tau}}.
\]

**Step D — Add slow integral to remove steady-state error**
\[
T_i \in \Big[\frac{8}{\omega_c},\,\frac{16}{\omega_c}\Big],\qquad
\boxed{K_i = \frac{K_p}{T_i}}.
\]
(Use the larger \(T_i\) for more phase margin; reduce \(T_i\) if steady-state is too slow.)

**Step E — Filter the derivative**
\[
\boxed{\tau_d \approx \frac{1}{10\,\omega_c}}
\]
This keeps derivative “active” near \(\omega_c\) but rolls off sensor noise.

**Summary (compute in this order):**
1. \(T_d = J/b\)
2. choose \(\omega_c\)
3. \(K_p = b\,\omega_c/K_\tau\)
4. \(K_d = K_p\,T_d\)
5. choose \(T_i\) in \([8,16]/\omega_c\) and set \(K_i = K_p/T_i\)
6. \(\tau_d \approx 1/(10\,\omega_c)\)

---

## 4) How to Verify

- **Bode of open loop \(L\)** → read PM/GM; aim for PM ≈ 45–65°.
- **Step of \(T\)** → check rise/overshoot/settling; integral ensures zero steady-state error.
- **Bode of \(S\)** → low-frequency \(|S|\) small is good for disturbance rejection.
- **Control effort** \(C/(1+L)\) → ensure commanded torque stays within limits (watch saturation; add anti-windup if needed).

---

## 5) Worked Example (numbers are illustrative)

Given \(J=0.01\) kg·m², \(b=0.001\) N·m·s/rad, \(K_\tau=K_t=0.10\) N·m/A:

- Mechanical pole: \(\omega_m=b/J=0.1\) rad/s  
- Choose \(\omega_c = 1.0\) rad/s (≈ \(10\times \omega_m\) after zero-placement we can push higher; conservative users may choose \(0.5\)–\(1.0\))
- \(T_d = J/b = 10\) s  
- \(K_p = b\,\omega_c/K_\tau = 0.001\times 1.0/0.1 = 0.010\)  
- \(K_d = K_p T_d = 0.010 \times 10 = 0.10\)  
- \(T_i = 8/\omega_c = 8\) s → \(K_i = K_p/T_i = 0.010/8 = 1.25\times10^{-3}\)  
- \(\tau_d \approx 1/(10\,\omega_c) = 0.10\) s

These gains typically yield **good PM** and a **well-damped** step.

---

## 6) Practical Notes & Troubleshooting

- **Too slow?** Increase \(\omega_c\) → raise \(K_p\); keep \(T_d=J/b\), reduce \(T_i\) (e.g., from \(16/\omega_c\) toward \(8/\omega_c\)), keep \(\tau_d \approx 1/(10\,\omega_c)\).
- **Ringing / low PM?** Lower \(\omega_c\) or move the zero slightly earlier (increase \(T_d\) a bit). If integral is aggressive, **increase \(T_i\)**.
- **Noisy control / encoder noise?** Increase \(\tau_d\) or lower \(\omega_c\).
- **Friction (Coulomb/stiction):** treat as a disturbance; stronger integral (smaller \(T_i\)) helps but watch overshoot and windup.
- **Gearing & load reflection:** if the gear ratio is \(N=\omega_m/\omega_L\),
  \[
  J = J_m + N^2 J_L,\qquad b = b_m + N^2 b_L,\qquad \theta_L=\frac{\theta_m}{N}.
  \]
- **Resonances / compliance:** a flexible shaft or two-mass load may need notch filters or an inner **velocity loop**.
- **Anti-windup:** clamp the integrator or back-calculate when torque saturates.

---

## 7) (Optional) Python Snippet to Plot Step & Bode

```python
import control as ctl, matplotlib.pyplot as plt

# Example parameters
J, b, K_tau = 0.01, 0.001, 0.10
omega_c = 1.0
T_d = J/b
Kp = b*omega_c/K_tau
Kd = Kp*T_d
Ti = 8/omega_c
Ki = Kp/Ti
tau_d = 1/(10*omega_c)

s = ctl.TransferFunction.s
G = 1/(s*(J*s+b))
C = Kp + Ki/s + (Kd*s)/(1+tau_d*s)

L = C*K_tau*G
T = ctl.feedback(L,1)
S = 1/(1+L)

# Margins
gm, pm, wg, wp = ctl.margin(L)
print(f"GM={gm:.2g} ({20*__import__('math').log10(gm):.1f} dB) @ {wg:.3g} rad/s, PM={pm:.1f}° @ {wp:.3g} rad/s")

# Plots
t, y = ctl.step_response(T)
plt.figure(); plt.plot(t,y); plt.grid(True); plt.title("Closed-loop Step"); plt.xlabel("Time [s]"); plt.ylabel("Position [rad]")
plt.figure(); ctl.bode(L, dB=True); plt.suptitle("Open-loop Bode"); plt.show()


