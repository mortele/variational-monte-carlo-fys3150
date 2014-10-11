from sympy import * 
import sys


var("r1,r2,r12,r1_2,r2_2,a,x1,y1,x2,y2")

R1 = Symbol('r1')
R2 = Symbol('r2')
R12 = Symbol('r12')
R1sq = Symbol('r1_2')
R2sq = Symbol('r2_2')

r1 = sqrt(x1**2+y1**2)
r2 = sqrt(x2**2+y2**2)
r1_2 = x1**2+y1**2
r2_2 = x2**2+y2**2
r12 = sqrt((x2-x1)**2 + (y2-y1)**2)


def gradient1(expr):
	return [diff(expr,x1), diff(expr,y1)]

def gradient2(expr):
	return [diff(expr,x2), diff(expr,y2)]

def laplacian(expr):
	gradx1,grady1 = gradient1(expr)
	gradx2,grady2 = gradient2(expr)	
	return diff(gradx1,x1) + diff(grady1,y1) + diff(gradx2,x2) + diff(grady2,y2)

wavefunc = exp(-a*(r1*r1+r2*r2))

def simplify(expr):
  return expr.factor().factor().collect(a).subs(r1,R1).subs(r1_2,R1*R1).factor()


print "gradient: "


#print printing.ccode(simplify(gradient1(wavefunc)[0].subs(r1,R1)))
#print printing.ccode(simplify(gradient1(wavefunc)[1].subs(r1,R1)))



print "\nlaplacian: "

#print printing.ccode(simplify(laplacian(wavefunc)))

print "\n\n", simplify(gradient1(wavefunc)[0].subs(r1,R1)), "\n\n"






