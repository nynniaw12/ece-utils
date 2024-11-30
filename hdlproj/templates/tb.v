`timescale 1ns/10ps

module ${PROJECT_NAME}_tb();
    reg clk = 0;
    reg rst_n;

    always #5 clk = ~clk;  // #period/2
    initial begin
        rst_n = 0;
        #100 rst_n = 1;
    end

    ${PROJECT_NAME} uut (
        .clk(clk),
        .rst_n(rst_n)
        // connections
    );

    initial begin
        @(posedge rst_n);
        // implement cases
        #1000;
        $finish;
    end
endmodule
