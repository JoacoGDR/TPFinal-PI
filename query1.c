void query1(aeropADT * lista){   // Recibe la lista ordenada por movimientos
	
	FILE * destino;
	destino = fopen("movimientos_aeropuerto.csv", "wt");   // Va a crear este archivo y va a poner todo ahi

	aeropADT * aux = lista;

	while(aux != NULL){
		fprintf(destino, "%s | %s | %ld \n", aux->oaci, aux->denom, aux->cantMov);
		aux = aux->next;
	}

	fclose(destino);
}
