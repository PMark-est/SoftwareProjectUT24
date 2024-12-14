describe('Extended search test', () => {
  it('should select "string:word" from the dropdown', () => {
    // Visit the page
    cy.visit('http://andmebaas.zapto.org');

    // Activate the "Extended" tab
    cy.get('li.extended > a')
      .should('be.visible')
      .click();

    // Select "string:word" from the dropdown
    cy.get(
      '#query_table > div > div > extended-token > div > div.args > div > extended-and-token > div > div:nth-child(2) > div > extended-cqp-term > div > div.pr-1.inline-block.align-middle.ml-2 > div.arg_selects.word > select.arg_type',
      { timeout: 10000 }
    )
      .should('be.visible')
      .select('word')
      .should('have.value', 'string:word');

      cy.get(
        '#query_table > div > div > extended-token > div > div.args > div > extended-and-token > div > div:nth-child(2) > div > extended-cqp-term > div > div.pr-1.inline-block.align-middle.ml-2 > div.arg_val_container > extended-cqp-value > input',
        { timeout: 10000 }
      )
        .should('be.visible') // Ensure the input is visible
        .clear() // Clear any existing value
        .type('raske') // Enter the value
        .should('have.value', 'raske'); // Verify the entered value
  
      cy.get('#content > searchtabs > div > div.tabbable.search_tabs.ng-isolate-scope > div > div.tab-pane.ng-scope.active > div > extended-standard > div > search-submit')
      .should('be.visible')
      .click();

      cy.get('table.results_table.kwic tbody tr.sentence')
  .then(($rows) => {
    // Skip the first row and iterate over the remaining rows
    cy.wrap($rows.slice(1)).each(($row) => {
      cy.wrap($row).should('contain.text', 'raske');
    });
  });

  });
});
