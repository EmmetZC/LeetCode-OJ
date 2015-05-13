import pylab
import sys

dash_style = (
    (0, 20, -15, 30, 10),
    (1, 30, 0, 15, 10),
    (0, 40, 15, 15, 10),
    (1, 20, 30, 60, 10),
    )

fig = pylab.figure()
ax = fig.add_subplot(111)

xs = []
ys = []

with open(sys.argv[1], "r") as f:
	n = int(f.readline())
	for i in range(n):
		x, y = [float(x) for x in f.readline().split()]
		xs.append(x)
		ys.append(y)
		ax.plot(x, y, marker='o')
		(dd, dl, r, dr, dp) = dash_style[1 if i == 22 else (i % 2)]
		#print 'dashlen call', dl
		t = ax.text(x, y, str(i), withdash=True,
               dashdirection=dd,
               dashlength=dl,
               rotation=r,
               dashrotation=dr,
               dashpush=dp,
               )
	xs.append(xs[0])
	ys.append(ys[0])
	ax.plot(xs,ys)
pylab.show()
