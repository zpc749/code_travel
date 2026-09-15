// 4. 股票问题


// 买卖股票最佳时机1——121
// dp[i][0]: 持股
// dp[i][1]: 不持股
dp[i][0] = max(dp[i-1][0], -prices[i]);
dp[i][1] = max(dp[i-1][1], dp[i-1][1] + prices[i]);



// 2——122
// dp[i][0]: 持股
// dp[i][1]: 不持股
dp[i][0] = max(dp[i-1][0], dp[i-1][1]-prices[i]);
dp[i][1] = max(dp[i-1][1], dp[i-1][1] + prices[i]);



// 3、4——123、188
// dp[i][0] 不操作
// dp[i][1] 第一次入股
// dp[i][2] 第一次出股
// dp[i][3] 第二次
// dp[i][4] 第三次.........

dp[i][0] = dp[i-1][0];
dp[i][1] = max(dp[i-1][1], -prices[i]);
dp[i][2] = max(dp[i-1][2], dp[i-1][1] + prices[i]);
dp[i][3] = max(dp[i-1][3], dp[i-1][2] - prices[i]);
dp[i][4] = max(dp[i-1][4], dp[i-1][3] + prices[i]);



// 含冷冻期——309
// dp[i][0] 
// dp[i][1] 
// dp[i][2] 
// dp[i][3] 

dp[i][0] = max(dp[i-1][0], tmp);
dp[i][1] = max(dp[i-1][1], dp[i-1][3]);
dp[i][2] = dp[i-1][0] + prices[i];
dp[i][3] = dp[i-1][2];



// 含手续费——714
// dp[i][0]: 持股
// dp[i][1]: 不持股
dp[i][0] = max(dp[i-1][0], dp[i-1][1]-prices[i]);
dp[i][1] = max(dp[i-1][1], dp[i-1][1] + prices[i] - fee);
