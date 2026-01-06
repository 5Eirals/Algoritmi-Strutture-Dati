#include "pg.h"

static stat_t sumStats(stat_t a, stat_t b){
	stat_t sum;
	sum.hp = a.hp + b.hp;
	sum.mp = a.mp + b.mp;
	sum.atk = a.atk + b.atk;
	sum.def = a.def + b.def;
	sum.mag = a.mag + b.mag;
	sum.spr = a.spr + b.spr;
	return sum;
}

static void calcEqStats(pg_t* pgp, invArray_t invArray){
	stat_t total = pgp->eq_stat;
	for(int i = 0; i < equipArray_inUse(pgp->equip); i++){
		total = sumStats(total, invArray_getByIndex(invArray, equipArray_getEquipByIndex(pgp->equip, i))->stat);
	}
	pgp->eq_stat = total;
}

int pg_read(FILE *fp, pg_t *pgp) {
	fscanf(fp, "%s %s %s",
		pgp->cod,
		pgp->nome,
		pgp->classe);
	stat_read(fp, &pgp->b_stat);
	return 1;
}

void pg_clean(pg_t *pgp) {
	equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray) {
	fprintf(fp, "| > %s\n"
		 "| %s \n| Class:%s\tEquipment:\n",
		 pgp->cod, pgp->nome, pgp->classe);
	equipArray_print(fp, pgp->equip, invArray);
	calcEqStats(pgp, invArray);
	stat_t stats = sumStats(pgp->eq_stat, pgp->b_stat);
	stat_print(fp, &stats, 0);
}

void pg_updateEquip(pg_t *pgp, invArray_t invArray) {
	equipArray_update(pgp->equip, invArray);
}

void pg_copy(pg_t* dest, pg_t* src) {
	strcpy(dest->cod, src->cod);
	strcpy(dest->nome, src->nome);
	strcpy(dest->classe, src->classe);
	dest->b_stat.hp = src->b_stat.hp;
	dest->b_stat.mp = src->b_stat.mp;
	dest->b_stat.atk = src->b_stat.atk;
	dest->b_stat.def = src->b_stat.def;
	dest->b_stat.mag = src->b_stat.mag;
	dest->b_stat.spr = src->b_stat.spr;
}



