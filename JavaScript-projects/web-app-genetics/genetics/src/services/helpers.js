//Deep clone array
// const clone = items =>
//   items.map(item => (Array.isArray(item) ? clone(item) : item))

export const round = (value, base) => {
  return Math.round(value * base) / base
}
