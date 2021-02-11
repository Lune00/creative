<template lang="">
  <div>
    <table>
      <thead>
        <tr>
          <th :colspan="alleles.length + 1">Rules between alleles</th>
        </tr>
      </thead>
      <tbody>
        <tr>
          <td>Allele</td>
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
import { Model } from '@/models/model-helpers.js'
import { round } from '@/services/helpers.js'
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
      const value = Model.rules.getValue(this.rules, allele_i.id, allele_j.id)
      return round(value, 10)
    },
    changeRule(event, allele_i, allele_j) {
      const target_rule = Model.rules.get(this.rules, allele_i.id, allele_j.id)
      const new_value = parseFloat(event.target.value)
      const rounded = round(new_value, 10)
      target_rule.value = allele_i.id > allele_j.id ? 1 - rounded : rounded
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
