CC = gcc
LDLIBS = -lcs50 -lm

# Make를 해서 Compile하는 기본 형식을 정한다.
%: %.c
	$(CC) $< -o $@ $(LDLIBS)