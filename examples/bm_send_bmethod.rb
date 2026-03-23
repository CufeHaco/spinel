# send_bmethod benchmark (from yjit-bench)
# define_method replaced with def (equivalent for AOT)

def zero
  0
end

def one(arg)
  arg
end

total = 0
n = 0
while n < 500000
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  zero
  total = total + one(123)
  n = n + 1
end
puts total
puts "done"
