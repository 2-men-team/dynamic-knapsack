from sys import argv

def readIn(infile):
  with open(infile) as fin:
    data = [list(map(lambda num: int(num), line.split())) for line in fin]
  return data[0][0], data[1:]

def writeOut(val, outfile):
  with open(outfile, 'w') as fout:
    fout.write(str(val))

def execute(cap, data):
  memo = [[0 for _ in xrange(cap + 1)] for _ in xrange(len(data) + 1)]
  minWeight = min(map(lambda el: el[1], data))

  for n in xrange(1, len(data) + 1):
    price, weight = data[n - 1]
    for w in xrange(minWeight, cap + 1):
      if weight > w:
        memo[n][w] = memo[n - 1][w]
      else:
        memo[n][w] = max(memo[n - 1][w], price + memo[n - 1][w - weight])

  return memo[len(data)][cap]

if __name__ == '__main__':
  infile = argv[1]
  outfile = 'ip71_teliman_08_output.txt'

  capacity, data = readIn(infile)
  summed = execute(capacity, data)
  writeOut(summed, outfile)
