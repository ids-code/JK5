require 'rake/clean'

CC = "clang++"
OPT = "-g -Wall -I/opt/local/include/opencv -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lm"
BINS = FileList["**/bin/*"]
BIN_DISTDIR = "./bin"

CLEAN.include()
CLOBBER.include(BINS)

directory BIN_DISTDIR
rule /.*/ => BIN_DISTDIR do |t,args|
  sh "#{CC} #{'src/'+t.name+'.cc'} -o #{t.name} #{OPT}"
  sh "mv #{t.name} #{t.name+'.dSYM'} bin"
end

task :all => [:all01, :all02] do 
end

task :all01 => ['grayscale', 'binary', 'imageInfo'] do
end

task :all02 => ['equalize', 'gammaCV', 'histogram', 'histogramCV'] do
end

# 動かないので誰かなんとかして
task :setAlias do
  sh "bash -ci 'alias page=\'ls\''"
  # sh "alias cv++=\'clang++ #{OPT}\'"
end