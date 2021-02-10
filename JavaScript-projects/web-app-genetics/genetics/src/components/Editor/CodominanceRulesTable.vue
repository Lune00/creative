<template lang="">
    <div>
        {{alleles}}
    </div>
</template>
<script>
export default {
    name: "CodominanceRulesTable",
    props: {
        alleles: {
            type: Array,
            required: true
        }
    }
}
</script>
<style lang="">
    
</style>