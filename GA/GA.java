import java.util.*;

public class GA {

    public static ArrayList<Gene > population = new ArrayList<Gene >();

    public static ArrayList<Integer> fitnessGenerator(ArrayList<Gene > population, ArrayList<Integer> avg_marks, int k){
        ArrayList<Integer> fitnessValue = new ArrayList<>();
        for(Gene g : population){
            ArrayList<Integer> individual = g.indices;
            int sumOfDelta=0;
            List<Integer> tmp;
            int idx=0;
            for(int i =0;i<k;i++){

                tmp = avg_marks.subList(idx, individual.get(i));
                if(tmp.size()>1) {
                    sumOfDelta = sumOfDelta+ Collections.max(tmp) - Collections.min(tmp);
                    idx = individual.get(i);
                } else {
                    sumOfDelta = sumOfDelta+avg_marks.get(0);
                }
            }
            g.fitnessValue = sumOfDelta;
        }

        return fitnessValue;
    }

    public static ArrayList<Gene > populater(int k, int n){

        //Let's make a hundred individuals
        Random randGen = new Random();

        ArrayList<Gene > population1 = new ArrayList<Gene >(100);


        for(int j=0;j<100;j++) {
            ArrayList<Integer> individual = new ArrayList<>();
            Gene g = new Gene();
            for (int i = 0; i < k; i++) {
                individual.add(randGen.nextInt(n));
            }
            individual.add(n);
            Collections.sort(individual);
            g.indices = individual;
            population1.add(g);
//            individual.clear();
        }
        return population1;
    }

    public static ArrayList<Gene > crossover(ArrayList<Gene > population1){

        for(int i=0; i<99; i++){
            Gene g1 = population1.get(i);
            Gene g2 = population1.get(i + 1);

            ArrayList<Integer> g1index = g1.indices;
            ArrayList<Integer> g2index = g2.indices;

            int length = g1index.size();


            ArrayList<Integer> g1indexAlt = new ArrayList<>();
            ArrayList<Integer> g2indexAlt = new ArrayList<>();

            g1indexAlt.addAll(g1index.subList(0, (length)/2));
            g1indexAlt.addAll(g2index.subList((length)/2, length));

            g2indexAlt.addAll(g2index.subList(0, (length)/2));

            g2indexAlt.addAll(g1index.subList((length)/2, length));

            g1.indices = g1indexAlt;
            g2.indices = g2indexAlt;

        }

        return population1;
    }

    public static ArrayList<Gene > mutate(ArrayList<Gene > population1) {
        Random random = new Random();
        int length = population1.get(0).indices.size();

        for(int i=0; i<100; i++) {


            int rand = 0;
            while (true) {
                rand = random.nextInt(11);
                if (rand != 0) break;
            }
            if (rand == 4) {
                //mutating, 1/10 chance to mutuate
                int site =0;
                if(population1.get(i).indices.get(site) != population1.get(i).indices.get(site+1))
                    if(population1.get(i).indices.get(site) >0)
                population1.get(i).indices.set(site, population1.get(i).indices.get(site)- 1);



            }
        }




        return population1;
    }



    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int avg=0;

        ArrayList<Integer> subject_1 = new ArrayList<>() ,
                           subject_2 = new ArrayList<>() ,
                           subject_3 = new ArrayList<>() ,
                           subject_4 = new ArrayList<>() ,
                           subject_5 = new ArrayList<>() ;

        ArrayList<Integer> avg_mark = new ArrayList<>();
        ArrayList<Integer> fitnessValue = new ArrayList<>();


        Random randGen = new Random();

        System.out.println("Enter number of students:");
        int n = sc.nextInt();
        System.out.println("Enter number of groups:");
        int k = sc.nextInt();

        for(int i =0; i<n;i++){
            subject_1.add(randGen.nextInt(101));
            subject_2.add(randGen.nextInt(101));
            subject_3.add(randGen.nextInt(101));
            subject_4.add(randGen.nextInt(101));
            subject_5.add(randGen.nextInt(101));
        }
        for(int i =0; i<n;i++){
            avg = subject_1.get(i) + subject_2.get(i) + subject_3.get(i) + subject_4.get(i) + subject_5.get(i);
            avg_mark.add(avg/5);
        }

        Collections.sort(avg_mark);
        //intial population
        population = populater(k-1, n);

        for(int it=0;it<100;it++) {
            fitnessValue = fitnessGenerator(population, avg_mark, k);

            population.sort(new Comparator<Gene>() {
                @Override
                public int compare(Gene o1, Gene o2) {
                    if(o1.fitnessValue> o2.fitnessValue){
                        return 1;
                    } else if(o1.fitnessValue < o2.fitnessValue)  {
                        return -1;
                    } else {
                        return 0;
                    }
                }
            });

            //CROSSOVER
            population = crossover(population);

            //MUTATE
            population = mutate(population);



        }

//        for(int i =0; i<n;i++){
//            System.out.println("Average mark  " + i + ":" + avg_mark.get(i));
//        }
//
        for(int i =0; i<100;i++) {
            System.out.format("Individual #"+ i +": ");
            for (int j = 0; j < k; j++)
                System.out.format(" %4d ", population.get(i).indices.get(j));


            System.out.println(" FITNESS VALUE:" + population.get(i).fitnessValue);
        }
        
        System.out.println("BEST: " + population.get(0).indices);




        //Debugging - print all marks
     /*   for(int i =0; i<n;i++){
            System.out.format("%4d %4d %4d %4d %4d \n", subject_1.get(i), subject_2.get(i), subject_3.get(i), subject_4.get(i), subject_5.get(i));
        }
      */


    }
}
