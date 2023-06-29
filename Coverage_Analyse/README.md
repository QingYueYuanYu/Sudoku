# 质量测试

## 生成测试文件

    g++ -fprofile-arcs -ftest-coverage -o Sudoku Sudoku.cpp Game.cpp Board.cpp Cell.cpp

## 运行测试文件

    ./Sudoku -c 5 -n 2 -m 2 -r 20~25 -u

## 查看测试结果

    // 生成测试结果文件coverage.info
    lcov --capture --directory . --output-file coverage.info
    // 将文件可视化到文件夹out下
    genhtml coverage.info --output-directory out
