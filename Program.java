import java.io.*;
import java.util.*;
class Program {
	public static int explore(int[][]board, int[][]marked, int node) {
		ans = 0;
		int n = board.length;
		for(int i=0; i<n; i++) {
			if(board[i][node]==1 && marked[i][node]==0) {
				marked[i][node] = 1;
				marked[node][i] = 1;
				ans = Math.max(ans, 1+explore(board, marked, i));
				marked[i][node] = 0;
				marked[node][i] = 0;
			}
		}
		return ans;
	}

	public static int longestPath(int[][]board ) {
		int ans = 0;
		int n = board.length;
		for(int i=0; i<n; i++) {
			int[][]visit = new int[n][n];
			ans = Math.max(ans, explore(board, visit, i));
		}
		return ans;
	}

	public static void main(String[]args) throws IOException{
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
		String line = input.readLine().trim();
		while(!line.equals("0 0")) {
			String[]frst = line.split("\\s+");
			int n = Integer.parseInt(frst[0]);
			int m = Integer.parseInt(frst[1]);
			int[][]graph = new int[n][n];
			for(int i=0; i<m; i++) {
				line = input.readLine().trim();
				String[]temp = line.split("\\s+");
				int a = Integer.parseInt(temp[0]);
				int b = Integer.parseInt(temp[1]);
				graph[a][b] = 1;
				graph[b][a] = 1;
			}
			System.out.println(longestPath(graph));
			line = input.readLine().trim();
		}
	}
}
