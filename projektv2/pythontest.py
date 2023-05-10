import time 
from common.methods import set_progress 
start = time.time() 
def Fibonacci(n): 
	if n < 0: 
		print("Incorrect input") 
	elif n == 0: 
		return 0 
	elif n == 1 or n == 2: 
		return 1 
	else: 
		return Fibonacci(n-1) + Fibonacci(n-2) 
result_fib=Fibonacci(40) 
print(result_fib) 
set_progress(result_fib) 
end=time.time() 
total_time=end-start print(total_time) 
set_progress(total_time)
set_progress(total_time)
