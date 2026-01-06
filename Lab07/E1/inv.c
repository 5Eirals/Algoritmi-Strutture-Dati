#include "inv.h"

static int max(int a, int b) {
	return a > b ? a : b;
}

void stat_read( FILE *fp, stat_t *statp) {
	fscanf( fp, " %d %d %d %d %d %d ",
		&statp->hp,
		&statp->mp,
		&statp->atk,
		&statp->def,
		&statp->mag,
		&statp->spr
		);
}

void stat_print( FILE *fp, stat_t *statp, int soglia) {
	fprintf(fp, " hp:%.3d mp:%.3d atk:%.3d def:%.3d mag:%.3d spr:%.3d\n",
		  statp->hp > soglia ? statp->hp : 1,
		  statp->mp > soglia ? statp->mp : 1,
		  statp->atk > soglia ? statp->atk : 1,
		  statp->def > soglia ? statp->def : 1,
		  statp->mag > soglia ? statp->mag : 1,
		  statp->spr > soglia ? statp->spr : 1
	);
}

void inv_read(FILE *fp, inv_t *invp) {
 	fscanf( fp, " %s %s ",
		invp->name,
		invp->type
		);
	stat_read(fp, &invp->stat);
}

void inv_print(FILE *fp, inv_t *invp) {
	int width = max(strlen(invp->name), strlen(invp->type)) + 2;
	fprintf(fp, "%.*s\n", LN_LEN, SEPARATOR);
	fprintf(fp, " Name: %*.*s%s\n",
		   width-strlen(invp->name),
		   width-strlen(invp->name),
		   SPACER,
		   invp->name
		   );
	fprintf(fp, " Class: %*.*s%s\n",
		   width-strlen(invp->type),
		   width-strlen(invp->type),
		   SPACER,
		   invp->type);
	stat_print(fp, &invp->stat, 0);
	fprintf(fp, "%.*s\n", LN_LEN, SEPARATOR);
}

stat_t inv_getStat(inv_t *invp) {
	return invp->stat;
}

