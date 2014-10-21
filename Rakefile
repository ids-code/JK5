require 'rake/clean'

CC = "clang++"
OPT = "-g -Wall -I/opt/local/include/opencv -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lm"
BINS = FileList["**/bin/*"]

CLEAN.include()
CLOBBER.include(BINS)

rule /.*/ do |t,args|
  sh "#{CC} #{'src/'+t.name+'.cc'} -o #{t.name} #{OPT}"
  sh "mv #{t.name} #{t.name+'.dSYM'} bin"
end

# 動かないので誰かなんとかして
task :setAlias do
  sh "alias cv++='clang++ -g -I/opt/local/include/opencv -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lm'"
end