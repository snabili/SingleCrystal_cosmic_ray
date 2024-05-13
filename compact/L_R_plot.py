import matplotlib.pyplot as plt
import matplotlib.axis as axis
import numpy as np
import time

angles = np.array([-90, -80, -70, -60, -50, -40, -30, -20, -10, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90])

l_r_data = np.array([-0.061246612, -0.158807588, -0.192411924, -0.232520325, -0.248780488, -0.215176152, -0.198915989, -0.179403794, -0.1100271, -0.036314363, 0.069918699, 0.155555556, 0.178319783, 0.185907859, 0.201084011, 0.195663957, 0.151219512, 0.127371274, -0.00596206])

l_r_sim = np.array([-0.06675, -0.21647, -0.24658, -0.25862, -0.25237, -0.2042, -0.20555, -0.16959, -0.07753, -1.62E-05, 0.078283, 0.169753, 0.205013, 0.203737, 0.251963, 0.258461, 0.247197, 0.218475, 0.06307])

y_axis_ticks = np.array([-0.3,-0.2,-0.1,0,0.1,0.2,0.3])

fig = plt.figure()
ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])

line1, = ax.plot(angles,l_r_data,"o", markersize = 5, label='Data')
line2, = ax.plot(angles,l_r_sim,"o", markersize = 5, label='MC')

ax.set_xlabel('angle (degree)')
ax.set_ylabel('(A-B)/(A+B)')
ax.set_title('Comparison of (A-B)/(A+B) vs. Angle for Simulation and Data')
ax.set_xticks(angles)
ax.set_yticks(y_axis_ticks)

#axis.XAxis.set_ticks(angles)
#axis.YAxis.set_ticks(y_axis_ticks)

ax.legend(handles=[line1, line2])
plt.show()
