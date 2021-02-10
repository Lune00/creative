export default{

    discreteNature(){
        return 'discrete'
    },
    continuousNature(){
        return 'continuous'
    },
    isFeatureDiscrete(nature){
        return 'discrete' === nature
    },
    isFeatureContinuous(nature){
        return 'continuous' === nature
    },
}