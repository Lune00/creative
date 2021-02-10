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
              <input type="number" step="0.1" min="0" max="1" />
            </template>
          </td>
        </tr>
      </tbody>
    </table>
  </div>
</template>
<script>
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
  computed: {}
}
</script>
<style lang="scss" scoped>
th {
  background: rgb(211, 211, 211);
  width: 100px;
  height: 16px;
}
</style>
