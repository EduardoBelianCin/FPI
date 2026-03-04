#include <stdio.h>

int main() {
    int d1,m1,a1; scanf("%d/%d/%d", &d1, &m1, &a1);
    int d2,m2,a2; scanf("%d/%d/%d", &d2, &m2, &a2);

    int amor = d1+m1+a1 + d2+m2+a2;
    amor *= 7;
    amor %= 101;
    printf("Amor: %d", amor);
    if(amor < 20) { printf("%% Pessimo dia para se apaixonar.\n"); }
    else if(amor <= 40) { printf("%% Melhor manter o coracao <3 longe de perigo.\n"); }
    else if(amor <= 69) { printf("%% Se o papo e as ideias baterem, esta liberado pensar em algo.\n"); }
    else if(amor <= 80) { printf("%% Saia com o coracao aberto, mas lembre, nem toda troca de olhar em onibus e sinal de romance.\n"); }
    else { printf("%% Um dia deslumbrantemente lindo para amar. Ps: Cuidado com a intensidade.\n"); }

    int sorte = (d1+d2 + m1+m2)*9 + (a2-a1);
    sorte %= 101;
    printf("Sorte: %d", sorte);
    if(sorte < 30) { printf("%% Nem jogue moedas pra cima hoje. Sem tigrinho nem jogos de azar, por favor!\n"); }
    else if(sorte <= 50) { printf("%% Melhor nao arriscar. Sem tigrinho nem jogos de azar, por favor!\n"); }
    else if(sorte <= 79) { printf("%% Por sua conta em risco. Sem tigrinho nem jogos de azar, por favor!\n"); }
    else if(sorte <= 90) { printf("%% Hoje vale a pena arriscar. Sem tigrinho nem jogos de azar, por favor!\n"); }
    else { printf("%% Nao tenha medo de virar cartas hoje. Sem tigrinho nem jogos de azar, por favor!\n"); }

    int trabalho = a1+a2 - (d1+d2 + m1+m2)*8;
    trabalho %= 101;
    printf("Trabalho: %d", trabalho);
    if(trabalho < 40) { printf("%% Hoje nao sera um dia tao proveitoso, keep calm e faca o basico.\n"); }
    else if(trabalho <= 50) { printf("%% Segura a emocao, nao xinga ninguem, nao esquece de beber agua.\n"); }
    else if(trabalho <= 69) { printf("%% Um dia proveitoso com certeza, leve sua simpatia consigo.\n"); }
    else if(trabalho <= 84) { printf("%% Boas vibracoes hoje, chances podem estar ao seu redor.\n"); }
    else { printf("%% Use do maximo de networking possível hoje, dia bom para negocios.\n"); }

    int cor = d1*d1 + d2*d2 + m1*m1 + m2*m2 + a1*a1 + a2*a2;
    cor %= 11;
    if(cor == 0) { printf("Cor: Cinza.\n"); }
    else if(cor == 1) { printf("Cor: Vermelho.\n"); }
    else if(cor == 2) { printf("Cor: Laranja.\n"); }
    else if(cor == 3) { printf("Cor: Amarelo.\n"); }
    else if(cor == 4) { printf("Cor: Verde.\n"); }
    else if(cor == 5) { printf("Cor: Azul.\n"); }
    else if(cor == 6) { printf("Cor: Roxo.\n"); }
    else if(cor == 7) { printf("Cor: Marrom.\n"); }
    else if(cor == 8) { printf("Cor: Rosa.\n"); }
    else if(cor == 9) { printf("Cor: Preto.\n"); }
    else if(cor == 10) { printf("Cor: Branco.\n"); }

    return 0;
}