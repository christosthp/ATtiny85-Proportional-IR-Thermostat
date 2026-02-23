The Core Concept
Instead of varying the intensity of the current, the system modulates the duration the heating element remains active within a fixed 20-second window. This effectively mimics an analog output using a digital "ON/OFF" approach.

Here is the breakdown of the logic based on the temperature differential (Difference = Setpoint - Current Temp):

1. Full Power Zone (Diff >= 1.5°C)
When the system is more than 1.5°C below the target, it operates at maximum capacity to reach the setpoint quickly.

ON Time: 20,000 ms (Full 20-second cycle)

Duty Cycle: 100% (Constantly ON)

UI Indicator: Thermometer icon active.

2. The Proportional Zone (0 < Diff < 1.5°C)
This is the "smart" region of the code. To prevent overshoot (where the temperature continues to rise past the target due to thermal inertia), the system scales the power linearly. The ON time is calculated via the formula:

onTime = (20000 / 15) * (Diff * 10)

Performance Examples:

1.0°C Difference: 13.3 sec ON | 6.7 sec OFF | ~66% Power

0.75°C Difference: 10.0 sec ON | 10.0 sec OFF | 50% Power

0.3°C Difference: 4.0 sec ON | 16.0 sec OFF | 20% Power

0.1°C Difference: 1.3 sec ON | 18.7 sec OFF | ~7% Power

3. Standby Zone (Diff <= 0)
Once the target temperature is met or exceeded, the system enters a safe standby state.

ON Time: 0 ms

Behavior: The heating element is fully deactivated.

UI Indicator: Thermometer icon hidden.

Key Takeaway
By utilizing Time Proportioned Control, we achieve stable temperatures and high efficiency without the need for expensive high-frequency switching hardware. This balance between full power and gradual approach ensures the system is both responsive and accurate.