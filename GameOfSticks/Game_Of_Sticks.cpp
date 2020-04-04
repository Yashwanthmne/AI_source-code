#include <bits/stdc++.h>


#define M 13
#define K 3


char player[4] = "MAX";


struct Node{
	int sticksRemaining;
	struct Node *left;
	struct Node *mid;
	struct Node *right;
};


int minimum(int a, int B){
	if (a < B){
		return a;
	}
	else{
		return B;
	}
}


int maximum(int a, int B){
	if (a > B){
		return a;
	}
	else{
		return B;
	}
}


char switchPlayer(){
	if (strcmp(player, "MAX") == 0){
		strcpy(player, "MIN");
	}
	else{
		strcpy(player, "MAX");
	}
}


struct Node *buildGameTree(int nsticks){
	struct Node *node = (struct Node *)calloc(1, sizeof(struct Node));
	node->sticksRemaining = nsticks;

	if (node->sticksRemaining >= 1){
		node->left = buildGameTree(nsticks - 1);
		switchPlayer();
	}
	if (node->sticksRemaining >=2){
		node->mid = buildGameTree(nsticks - 2);
		switchPlayer();
	}
	if (node->sticksRemaining >= K){
		node->right = buildGameTree(nsticks - K);
		switchPlayer();
	}

	return (node);
}


int computeMinimax(struct Node *n){
	int value;

	if (n->sticksRemaining == 0){
		if (strcmp(player, "MIN") == 0){
			return 1;
		}
		else{
			return -1;
		}
	}
	else{
		if (strcmp(player, "MIN") == 0){
			value = minimum(-1, computeMinimax(n->left));
			if (n->right != NULL){
				value = minimum(value, computeMinimax(n->right));
			}
			if (n->mid != NULL){
				value = minimum(value, computeMinimax(n->mid));
			}
		}
		else{
			value = maximum(1, computeMinimax(n->left));
			if (n->right != NULL){
				value = maximum(value, computeMinimax(n->right));
			}
			if (n->mid != NULL){
				value = maximum(value, computeMinimax(n->mid));
			}
		}
	}

	return value;

}


main(){
	struct Node *root = buildGameTree(M);
	int r;

	printf("WELCOME TO THE GAME\n");
	srand(time(NULL));

	while (true){
		int takenSticks = 0;
		int v1,v2,v3;

		v1 = computeMinimax(root->left);
		if (root->right != NULL){
			v2 = computeMinimax(root->right);
		}
		else{
			v2 = 2;
		}
		if(root -> mid != NULL){
			v3 = computeMinimax(root->mid);
		} else {
			v3 = 3;
		}
		
		printf("V1: %d V2: %d V3: %d\n", v1, v2, v3);

		if (v1 < v2 && v1 < v3){
			takenSticks = 1;
		}
		else if(v2 < v1 && v2 < v3){
			takenSticks = K;
		}
		else if(v3 < v1 && v3 < v2){
			takenSticks = 2;
		}
		
		else{
			r = ((double)rand() / (RAND_MAX)) + 2;
			if (r == 0){
				takenSticks = 1;
			}
			if (r == 1){
				takenSticks = 2;
			}
			if (r == 2){
				takenSticks = 3;
			}
		}


		if (takenSticks == 1){
			root = root->left;
		}
		else if (takenSticks == 2){
			root = root->mid;
		}
		if(takenSticks == K){
			root = root->right;
		}

		printf("MAX player(PC) takes %d cubes, remaining %d cubes\n", takenSticks, root->sticksRemaining);
		if (root->sticksRemaining == 0){
			printf("MAX player(PC) wins the game!");
			break;
		}

 
		do{
			printf("How many cubes do you want? ");

			scanf("%d", &takenSticks);
			if ((takenSticks >= 1 && takenSticks <= K) && root->sticksRemaining - takenSticks >= 0){
				break;
			}
			printf("That's an illegal move. Choose 1, 2 or 3 sticks.\n");

		} while (true);

		if (takenSticks == 1){							
			root = root->left;
		}
		else if (takenSticks == 2){
			root = root->mid;
		}
		else {
			root = root->right;
		}


		printf("MIN player(human) takes %d cubes, leaving %d\n", takenSticks, root->sticksRemaining);

		if (root->sticksRemaining == 0){
			printf("MIN player(human) wins the game!");
			break;
		}
	}
}
