var groups = new Int64[] {0, 0, 0, 0, 0, 0, 0, 0, 0};

// read a file
var data = File.ReadAllLines("./input.txt")[0];
var seed = from x in data.Split(',')
            select Int64.Parse(x);

foreach(var fish in seed) {
  groups[fish]++;
}

for(int i=0; i<256; i++) {
  groups = new Int64[] {
    groups[1], groups[2], groups[3],
    groups[4], groups[5], groups[6],
    groups[0]+groups[7], groups[8], groups[0]
  };
  //foreach(var g in groups) {
  //  Console.Write(g);
  //  Console.Write('\t');
  //}
  //Console.WriteLine();
}

var sum = groups.Sum();
Console.WriteLine(sum);
