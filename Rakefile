require 'rake/clean'
CC = "clang++ -g -I/opt/local/include/opencv -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lm"
SRCS = FileList["**/*.cc"]
OBJS = SRCS.ext('dSYM')

CLEAN.include(OBJS)

file "hello" do |t|
  sh "#{CC} -o #{t.name} #{t.prerequisites.join(' ')}"
end

task :setAlias do
  sh "alias cv++='clang++ -g -I/opt/local/include/opencv -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lm'"
end