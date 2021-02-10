<template lang="">
    <div>
        <div>{{ Object.keys(allele) }} - {{ Object.values(allele) }}</div>
    </div>
</template>
<script>

import Allele from '@/models/Allele.js'

export default {
    name: "AlleleRow",
    props: {
        allele:{
            type: Object,
            required: true,
            validator: function(allele){
                return allele instanceof Allele
            }
        }
    }
}
</script>
<style lang="">
    
</style>