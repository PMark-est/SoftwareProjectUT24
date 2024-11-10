/** @format */
import angular from "angular";
import _ from "lodash";
import extendedComponents from "./widgets";

angular.module("korpApp").component("extendedCqpValue", {
    bindings: {
        change: "&",
        attributeDefinition: "<",
        term: "<",
    },
    controller: [
        "$scope",
        "$controller",
        "$compile",
        "$element",
        "$http", // Include $http for AJAX requests
        function ($scope, $controller, $compile, $element, $http) {
            const ctrl = this;

            let prevScope = null;
            let modelChildWatch = null;
            let flagsChildWatch = null;

            ctrl.$onChanges = (changeObj) => {
                if (changeObj.attributeDefinition && ctrl.attributeDefinition) {
                    updateComponent(!changeObj.attributeDefinition.isFirstChange());
                }
            };

            function updateComponent(initialized) {
                if (initialized && ctrl.term.flags) {
                    // selected attribute changed
                    delete ctrl.term.flags["c"];
                }

                if (prevScope != null) {
                    prevScope.$destroy();
                }

                if (modelChildWatch) {
                    modelChildWatch();
                    flagsChildWatch();
                }

                const childScope = $scope.$new();
                modelChildWatch = childScope.$watch("model", (val) => {
                    ctrl.change({ term: { val } });
                });
                flagsChildWatch = childScope.$watch(
                    "orObj.flags",
                    (val) => {
                        ctrl.change({ term: { flags: val } });
                    },
                    true
                );

                // Preserve `orObj` name for backward compatibility with components
                childScope.orObj = ctrl.term;
                _.extend(childScope, ctrl.attributeDefinition);
                childScope.model = ctrl.term.val;

                // Fetch the dataset from the server
                const apiUrl = `http://andmebaas.zapto.org:8080/lexicon?positional_attribute=${encodeURIComponent(
                    ctrl.attributeDefinition.value
                )}`;
                
                $http.get(apiUrl).then(
                    (response) => {
                        // Extract and filter dataset
                        const fetchedData = response.data.Arguments || [];
                        const filteredData = fetchedData.filter(
                            (item) => item && !item.startsWith("#") && !item.startsWith("<")
                        );
                        const dataset = filteredData.map((item) => [item, item]);

                        // Configure template and controller
                        let template, controller;
                        const locals = { $scope: childScope };
                        prevScope = childScope;

                        if (ctrl.attributeDefinition["extended_component"]) {
                            const def =
                                extendedComponents[
                                    ctrl.attributeDefinition["extended_component"].name ||
                                    ctrl.attributeDefinition["extended_component"]
                                ];
                            if (_.isFunction(def)) {
                                ({ template, controller } = def(
                                    ctrl.attributeDefinition["extended_component"].options
                                ));
                            } else {
                                ({ template, controller } = def);
                            }
                        } else {
                            controller = extendedComponents.datasetSelect({ attributes: dataset }).controller;
                            if (ctrl.attributeDefinition["extended_template"]) {
                                template = ctrl.attributeDefinition["extended_template"];
                            } else {
                                let tmplObj;
                                if (ctrl.attributeDefinition.value === "word") {
                                    tmplObj = { placeholder: "<{{'any' | loc:$root.lang}}>" };
                                } else {
                                    tmplObj = { placeholder: "" };
                                }

                                template = extendedComponents.datasetSelect({ attributes: dataset }).template;
                            }
                        }

                        // Compile and attach the template with controller
                        $controller(controller, locals);
                        const tmplElem = $compile(template)(childScope);
                        $element.html(tmplElem).addClass("arg_value");
                    },
                    (error) => {
                        console.error("Failed to fetch dataset:", error);
                    }
                );
            }
        },
    ],
});


