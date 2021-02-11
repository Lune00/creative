<template lang="">
  <div>
    <table>
      <thead>
        <tr>
          <th :colspan="alleles.length + 1">Règles</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td></td>
          <th v-for="(allele, index) in alleles" :key="index">
            {{ allele.key }}
          </th>
        </tr>
        <tr v-for="(allele_i, i) in alleles" :key="i">
          <th>{{ allele_i.key }}</th>
          <td v-for="(allele_j, j) in alleles" :key="j">
            <template v-if="allele_i.id === allele_j.id">
              <input
                type="number"
                step="0.1"
                min="0"
                max="1"
                readonly
                value="1"
              />
            </template>
            <template v-else>
              <input
                type="number"
                step="0.1"
                min="0"
                max="1"
                :value="rule(allele_i, allele_j)"
                @change="changeRule($event, allele_i, allele_j)"
              />
            </template>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>
<script>
import model from '@/models/model-helpers.js'
export default {
  name: 'CodominanceRulesTable',
  data() {
    return {}
  },
  props: {
    alleles: {
      type: Array,
      required: true
    },
    rules: {
      type: Array,
      required: true
    }
  },
  methods: {
    rule(allele_i, allele_j) {
      return model.getRuleValue(this.rules, allele_i.id, allele_j.id)
    },
    changeRule(event, allele_i, allele_j) {
      const target_rule = model.getRule(this.rules, allele_i.id, allele_j.id)
      const new_value = parseFloat(event.target.value)
      console.log(target_rule.value, new_value)
      target_rule.value = new_value
    }
  }
}
</script>
<style lang="scss" scoped>
th {
  background: rgb(211, 211, 211);
  width: 100px;
  height: 16px;
}
</style>
